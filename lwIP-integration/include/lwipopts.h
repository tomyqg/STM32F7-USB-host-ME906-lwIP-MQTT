#ifndef LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_
#define LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global defines
+---------------------------------------------------------------------------------------------------------------------*/

#define DEFAULT_ACCEPTMBOX_SIZE					16
#define DEFAULT_RAW_RECVMBOX_SIZE				16
#define DEFAULT_TCP_RECVMBOX_SIZE				16
#define DEFAULT_THREAD_PRIO						(UINT8_MAX / 2)
#define DEFAULT_THREAD_STACKSIZE				2048
#define DEFAULT_UDP_RECVMBOX_SIZE				16
#define LWIP_DEBUG								1
#define LWIP_DNS								1
#define LWIP_NETIF_API							1
#define LWIP_POSIX_SOCKETS_IO_NAMES				0
#define MEM_ALIGNMENT							4
#define MEM_SIZE								(10 * 1024)
#define MEMP_NUM_SYS_TIMEOUT					(LWIP_NUM_SYS_TIMEOUT_INTERNAL + 1)
#define NUM_PPP									1
#define PPPOS_SUPPORT							1
#define PPP_NOTIFY_PHASE						1
#define PPP_SUPPORT								1
#define PRINTPKT_SUPPORT						1
#define TCPIP_MBOX_SIZE							16
#define TCPIP_THREAD_PRIO						(UINT8_MAX / 2)
#define TCPIP_THREAD_STACKSIZE					4096
#define VJ_SUPPORT								0

#if LWIP_DEBUG == 1

#define LWIP_DBG_MIN_LEVEL						LWIP_DBG_LEVEL_ALL

#define API_LIB_DEBUG							LWIP_DBG_OFF
#define API_MSG_DEBUG							LWIP_DBG_OFF
#define AUTOIP_DEBUG							LWIP_DBG_OFF
#define DHCP_DEBUG								LWIP_DBG_OFF
#define DNS_DEBUG								LWIP_DBG_OFF
#define ICMP_DEBUG								LWIP_DBG_OFF
#define IGMP_DEBUG								LWIP_DBG_OFF
#define IP_DEBUG								LWIP_DBG_OFF
#define IP_REASS_DEBUG							LWIP_DBG_OFF
#define MEMP_DEBUG								LWIP_DBG_OFF
#define MEM_DEBUG								LWIP_DBG_OFF
#define MQTT_DEBUG								LWIP_DBG_ON
#define NETIF_DEBUG								LWIP_DBG_OFF
#define PBUF_DEBUG								LWIP_DBG_OFF
#define PPP_DEBUG								LWIP_DBG_ON
#define SOCKETS_DEBUG							LWIP_DBG_OFF
#define TCPIP_DEBUG								LWIP_DBG_OFF
#define TCP_CWND_DEBUG							LWIP_DBG_OFF
#define TCP_DEBUG								LWIP_DBG_OFF
#define TCP_FR_DEBUG							LWIP_DBG_OFF
#define TCP_INPUT_DEBUG							LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG						LWIP_DBG_OFF
#define TCP_QLEN_DEBUG							LWIP_DBG_OFF
#define TCP_RST_DEBUG							LWIP_DBG_OFF
#define TCP_RTO_DEBUG							LWIP_DBG_OFF
#define TCP_WND_DEBUG							LWIP_DBG_OFF
#define UDP_DEBUG								LWIP_DBG_OFF

#endif	/* LWIP_DEBUG == 1 */

/*---------------------------------------------------------------------------------------------------------------------+
| lwIP TCP/IP core locking
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Asserts that this function is not called from interrupt context and that lwIP's TCP/IP core is locked by
 * current thread.
 *
 * \sa LWIP_ASSERT_CORE_LOCKED()
 */

void lwipAssertCoreLocked(void);

/**
 * \brief Locks lwIP's TCP/IP core.
 *
 * \sa LOCK_TCPIP_CORE()
 */

void lwipLockTcpipCore(void);

/**
 * \brief Marks that lwIP's TCP/IP core is started.
 *
 * \sa LWIP_MARK_TCPIP_THREAD()
 */

void lwipMarkTcpipThread(void);

/**
 * \brief Unlocks lwIP's TCP/IP core.
 *
 * \sa UNLOCK_TCPIP_CORE()
 */

void lwipUnlockTcpipCore(void);

#define LOCK_TCPIP_CORE()						lwipLockTcpipCore()

#define LWIP_ASSERT_CORE_LOCKED()				lwipAssertCoreLocked()

#define LWIP_MARK_TCPIP_THREAD()				lwipMarkTcpipThread()

#define UNLOCK_TCPIP_CORE()						lwipUnlockTcpipCore()

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* LWIP_INTEGRATION_INCLUDE_LWIPOPTS_H_ */
