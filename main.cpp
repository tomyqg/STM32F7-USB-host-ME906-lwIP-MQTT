/**
 * \file
 * \brief Main code block.
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#define _GNU_SOURCE

#include "HuaweiMe906.hpp"
#include "openHuaweiMe906.hpp"
#include "PpposManager.hpp"

#include "stm32f7xx_hal.h"

#include "usbh_core.h"

#include "distortos/board/initializeStreams.hpp"

#include "distortos/distortosVersion.h"
#include "distortos/DynamicThread.hpp"
#include "distortos/ThisThread.hpp"

#include "lwip/apps/mqtt.h"

#include "lwip/tcpip.h"

#include <cstring>

/*---------------------------------------------------------------------------------------------------------------------+
| local defines
+---------------------------------------------------------------------------------------------------------------------*/

/// MQTT message published to ONLINE_TOPIC as client's "will" when connection is lost
#define OFFLINE_MESSAGE	"0"

/// MQTT "online" topic - OFFLINE_MESSAGE is published as client's "will" when connection is lost
#define ONLINE_TOPIC	"distortos/" DISTORTOS_VERSION_STRING "/" DISTORTOS_BOARD "/online"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local types
+---------------------------------------------------------------------------------------------------------------------*/

/// collection of data used by lwIP's MQTT client
struct MqttClient
{
	/// MQTT client connection info
	mqtt_connect_client_info_t connectionInfo;

	/// pointer to lwIP's MQTT client struct
	mqtt_client_t* client;

	/// MQTT client's status
	mqtt_connection_status_t status;

	/// true if connecting is in progress, false otherwise
	bool connecting;
};

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief lwIP's MQTT connection callback
 *
 * \param [in] client is a pointer to lwIP's MQTT client struct
 * \param [in] argument is a argument which was passed to mqtt_client_connect(), must be MqttClient!
 * \param [in] status is the status of MQTT connection
 */

void mqttClientConnectionCallback(mqtt_client_t* const client, void* const argument,
		const mqtt_connection_status_t status)
{
	assert(argument != nullptr);
	auto& mqttClient = *static_cast<MqttClient*>(argument);
	assert(client == mqttClient.client);

	fiprintf(standardOutputStream, "mqttClientConnectionCallback: status = %d\r\n", status);

	mqttClient.status = status;
	mqttClient.connecting = {};
}

/**
 * \brief Thread which constantly reads selected HuaweiMe906 serial port and prints data that was read on
 * \a standardOutputStream.
 *
 * \param [in] huaweiMe906 is a reference to HuaweiMe906 object
 * \param [in] port selects the serial port that will be accessed
 */

void readerThread(HuaweiMe906& huaweiMe906, const HuaweiMe906::Port port)
{
	const auto stream = openHuaweiMe906(huaweiMe906, port, "r");
	const auto portString = port == HuaweiMe906::Port::pcui ? "PCUI" :
			port == HuaweiMe906::Port::networkCard ? "Network card" : "GPS";

	while (1)
	{
		char buffer[128];
		if (fgets(buffer, sizeof(buffer), stream) != nullptr)
		{
			auto length = strlen(buffer);
			// trim trailing whitespace
			while (length > 0 && (buffer[length - 1] == '\r' || buffer[length - 1] == '\n'))
			{
				buffer[length - 1] = '\0';
				--length;
			}
			if (length > 0)
				fiprintf(standardOutputStream, "%s port, read %zu bytes: \"%s\"\r\n", portString, length, buffer);
		}
		else
		{
			fiprintf(standardOutputStream, "%s port, read failed, errno = %d\r\n", portString, errno);
			clearerr(stream);
			distortos::ThisThread::sleepFor(std::chrono::seconds{5});
		}
	}
}

/**
 * \brief User callback for USB host events.
 *
 * \param [in] host is a pointer to USB host
 * \param [in] event is the event
 */

void usbHostEventCallback(USBH_HandleTypeDef*, const uint8_t event)
{
	switch (event)
	{
		case HOST_USER_SELECT_CONFIGURATION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION");
			break;

		case HOST_USER_CLASS_ACTIVE:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CLASS_ACTIVE");
			break;

		case HOST_USER_CLASS_SELECTED:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CLASS_SELECTED");
			break;

		case HOST_USER_CONNECTION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CONNECTION");
			break;

		case HOST_USER_DISCONNECTION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_DISCONNECTION");
			break;

		case HOST_USER_UNRECOVERED_ERROR:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_UNRECOVERED_ERROR");
			break;

		default:
			USBH_UsrLog("usbHostEventCallback: event = %" PRIu8, event);
			break;
	}
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Main code block of application
 *
 * \return doesn't return
 */

int main()
{
	distortos::board::initializeStreams();

	fiprintf(standardOutputStream, "Started %s board\r\n", DISTORTOS_BOARD);

	USBH_HandleTypeDef usbHost {};
	{
		const auto ret = USBH_Init(&usbHost, usbHostEventCallback, 0);
		assert(ret == USBH_OK);

	}
	HuaweiMe906 huaweiMe906 {};
	huaweiMe906.registerClass(usbHost);
	{
		const auto ret = USBH_Start(&usbHost);
		assert(ret == USBH_OK);
	}

	const auto pcuiReaderThread = distortos::makeAndStartDynamicThread({2048, 1},
			readerThread, std::ref(huaweiMe906), HuaweiMe906::Port::pcui);
	const auto gpsReaderThread = distortos::makeAndStartDynamicThread({2048, 1},
			readerThread, std::ref(huaweiMe906), HuaweiMe906::Port::gps);

	tcpip_init({}, {});

	PpposManager ppposManager {huaweiMe906};
	ppposManager.initialize();

	MqttClient mqttClient {};

	LOCK_TCPIP_CORE();
	mqttClient.client = mqtt_client_new();
	assert(mqttClient.client != nullptr);
	UNLOCK_TCPIP_CORE();

	mqttClient.connectionInfo.client_id = "MQTT client";
	mqttClient.connectionInfo.client_user = {};
	mqttClient.connectionInfo.client_pass = {};
	mqttClient.connectionInfo.keep_alive = 60;
	mqttClient.connectionInfo.will_topic = ONLINE_TOPIC;
	mqttClient.connectionInfo.will_msg = OFFLINE_MESSAGE;
	mqttClient.connectionInfo.will_qos = {};
	mqttClient.connectionInfo.will_retain = {};
#if LWIP_ALTCP && LWIP_ALTCP_TLS
	mqttClient.connectionInfo.tls_config = {};
#endif

	// broker.hivemq.com -> 18.184.104.180
	const ip_addr_t ip = IPADDR4_INIT_BYTES(18, 184, 104, 180);

	while (1)
	{
		mqttClient.connecting = true;

		{
			LOCK_TCPIP_CORE();
			const auto ret = mqtt_client_connect(mqttClient.client, &ip, MQTT_PORT, mqttClientConnectionCallback,
					&mqttClient, &mqttClient.connectionInfo);
			UNLOCK_TCPIP_CORE();
			if (ret != ERR_OK)
			{
				fiprintf(standardOutputStream, "mqtt_client_connect() failed, ret = %d\r\n", ret);
				distortos::ThisThread::sleepFor(std::chrono::seconds{5});
				continue;
			}
		}

		while (mqttClient.connecting == true)
		{
			fiprintf(standardOutputStream, "Connecting to MQTT broker...\r\n");
			distortos::ThisThread::sleepFor(std::chrono::seconds{5});
		}

		while (mqttClient.status == MQTT_CONNECT_ACCEPTED)
			distortos::ThisThread::sleepFor(std::chrono::seconds{5});

		LOCK_TCPIP_CORE();
		mqtt_disconnect(mqttClient.client);
		UNLOCK_TCPIP_CORE();
	}
}

extern "C" void OTG_FS_IRQHandler(void)
{
	extern HCD_HandleTypeDef hhcd;
	HAL_HCD_IRQHandler(&hhcd);
}
