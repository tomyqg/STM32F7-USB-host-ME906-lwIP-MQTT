STM32F7-USB-host-ME906-lwIP-MQTT [![Build Status](https://travis-ci.org/DISTORTEC/STM32F7-USB-host-ME906-lwIP-MQTT.svg)](https://travis-ci.org/DISTORTEC/STM32F7-USB-host-ME906-lwIP-MQTT)
================================

MQTT demo project for [32F746GDISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) board, also known
as *STM32F746G-DISCO*. It features following components:
- *distortos*,
- *ST's* *STM32F7 HAL* and *USB host* libraries, with numerous fixes to make them actually usable,
- USB class driver for *Huawei ME906* modem,
- *lwIP*.

Configuration & building
------------------------

    $ mkdir output
    $ cd output
    $ cmake -C../distortosConfiguration.cmake .. -GNinja
    $ ninja

For more in-depth instructions see `distortos/README.md`.

MQTT
----

Once the modem connects to the network, it tries to connect to MQTT broker at `broker.hivemq.com`. When you subscribe to
the topic `distortos/#`, you should see the messages with device's online status (`1` is sent when the device connects,
`0` as a MQTT client's will once the connection is lost) and changes of button state:

```
$ mosquitto_sub -h broker.hivemq.com -t "distortos/#" -v
distortos/0.7.0/ST,32F746GDISCOVERY/online 1
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 0
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 1
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 0
```

The application also allows you to control on-board LEDs via MQTT:

```
# set the LED on
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state" -m "1"
# set the LED off
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state" -m "0"
```

Debug output
------------

ST-Link V2-1 has a virtual COM port which is used for debug output from the application. The stream uses typical
parameters: 115200 bps, 8N1. Below you will find the example of the produced output.

```
[2019-05-21 16:33:47] Started ST,32F746GDISCOVERY board
[2019-05-21 16:33:47] ppp phase changed[0]: phase=0
[2019-05-21 16:33:47] mqtt_client_connect: Connecting to host: 18.184.104.180 at port:1883
[2019-05-21 16:33:47] mqtt_client_connect: Error connecting to remote ip/port, -4
[2019-05-21 16:33:47] mqtt_client_connect() failed, ret = -4
[2019-05-21 16:33:47] PCUI port, read failed, errno = 128
[2019-05-21 16:33:47] GPS port, read failed, errno = 128
[2019-05-21 16:33:47] PpposManager::executeCommand: write failed, errno = 128
[2019-05-21 16:33:52] mqtt_client_connect: Connecting to host: 18.184.104.180 at port:1883
[2019-05-21 16:33:52] mqtt_client_connect: Error connecting to remote ip/port, -4
[2019-05-21 16:33:52] mqtt_client_connect() failed, ret = -4
[2019-05-21 16:33:52] PCUI port, read failed, errno = 128
[2019-05-21 16:33:52] GPS port, read failed, errno = 128
[2019-05-21 16:33:52] PpposManager::executeCommand: write failed, errno = 128
[2019-05-21 16:33:57] mqtt_client_connect: Connecting to host: 18.184.104.180 at port:1883
[2019-05-21 16:33:57] mqtt_client_connect: Error connecting to remote ip/port, -4
[2019-05-21 16:33:57] mqtt_client_connect() failed, ret = -4
[2019-05-21 16:33:57] PCUI port, read failed, errno = 128
[2019-05-21 16:33:57] GPS port, read failed, errno = 128
[2019-05-21 16:33:57] PpposManager::executeCommand: write failed, errno = 128
[2019-05-21 16:33:59] usbHostEventCallback: HOST_USER_CONNECTION
[2019-05-21 16:33:59] USB Device Attached
[2019-05-21 16:33:59] PID: 1573h
[2019-05-21 16:33:59] VID: 12d1h
[2019-05-21 16:33:59] Address (#1) assigned.
[2019-05-21 16:33:59] Manufacturer : HUAWEI Technology
[2019-05-21 16:33:59] Product : HUAWEI Mobile
[2019-05-21 16:33:59] Serial Number : ...
[2019-05-21 16:33:59] Enumeration done.
[2019-05-21 16:33:59] usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION
[2019-05-21 16:34:00] Default configuration set.
[2019-05-21 16:34:00] Device remote wakeup enabled
[2019-05-21 16:34:00] HuaweiMe906::SerialPort(0x2004faf0)::interfaceInitialize: interface 0,
                      read endpoint address 0x81, read endpoint size 64, read pipe 2,
                      write endpoint address 0x1, write endpoint size 64, write pipe 3
[2019-05-21 16:34:00] HuaweiMe906::SerialPort(0x2004fb5c)::interfaceInitialize: interface 2,
                      read endpoint address 0x83, read endpoint size 64, read pipe 4,
                      write endpoint address 0x3, write endpoint size 64, write pipe 5
[2019-05-21 16:34:00] HuaweiMe906::SerialPort(0x2004fbc8)::interfaceInitialize: interface 5,
                      read endpoint address 0x89, read endpoint size 64, read pipe 6,
                      write endpoint address 0x6, write endpoint size 64, write pipe 7
[2019-05-21 16:34:00] Huawei ME906 class started.
[2019-05-21 16:34:00] usbHostEventCallback: HOST_USER_CLASS_SELECTED
[2019-05-21 16:34:00] usbHostEventCallback: HOST_USER_CLASS_ACTIVE
[2019-05-21 16:34:02] mqtt_client_connect: Connecting to host: 18.184.104.180 at port:1883
[2019-05-21 16:34:02] mqtt_client_connect: Error connecting to remote ip/port, -4
[2019-05-21 16:34:02] mqtt_client_connect() failed, ret = -4
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004faf0)::requestRead: requesting 64 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004faf0)::backgroundProcess: received 29 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fbc8)::requestRead: requesting 64 bytes
[2019-05-21 16:34:02] PCUI port, read 25 bytes: "^HCSQ: "LTE",57,56,130,24"
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 5 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004faf0)::requestRead: requesting 64 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 5 bytes
[2019-05-21 16:34:02] PpposManager::executeCommand: wrote 5 bytes: "ATI"
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 29 bytes
[2019-05-21 16:34:02] PpposManager::executeCommand: read 27 bytes: "^HCSQ: "LTE",57,56,130,24"
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:02] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:02] PpposManager::executeCommand: read 45 bytes:
                      "Manufacturer: Huawei Technologies Co., Ltd."
[2019-05-21 16:34:03] PpposManager::executeCommand: read 15 bytes: "Model: ME906E"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 27 bytes: "Revision: 12.430.19.08.00"
[2019-05-21 16:34:03] PpposManager::executeCommand: read 23 bytes: "IMEI: ..."
[2019-05-21 16:34:03] PpposManager::executeCommand: read 14 bytes: "+GCAP: +CGSM"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 4 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 54 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 54 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 54 bytes:
                      "AT^SYSCFGEX="030201",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 6 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 11 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 11 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 11 bytes: "AT+COPS=0"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 6 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 44 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 44 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 44 bytes:
                      "AT+CGDCONT=1,"IP","internet","0.0.0.0",0,0"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 6 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 37 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 37 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 37 bytes:
                      "AT+CGDCONT=16,"IP","","0.0.0.0",0,0"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 6 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 12 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 12 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 12 bytes: "AT+CGATT=1"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 6 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 9 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 9 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: wrote 9 bytes: "ATD*99#"
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 21 bytes
[2019-05-21 16:34:03] PpposManager::executeCommand: read 19 bytes: "CONNECT 100000000"
[2019-05-21 16:34:03] ppp_connect[0]: holdoff=0
[2019-05-21 16:34:03] ppp phase changed[0]: phase=3
[2019-05-21 16:34:03] pppos_connect: unit 0: connecting
[2019-05-21 16:34:03] ppp_start[0]
[2019-05-21 16:34:03] ppp phase changed[0]: phase=6
[2019-05-21 16:34:03] pppos_send_config[0]: out_accm=FF FF FF FF
[2019-05-21 16:34:03] ppp_send_config[0]
[2019-05-21 16:34:03] pppos_recv_config[0]: in_accm=FF FF FF FF
[2019-05-21 16:34:03] ppp_recv_config[0]
[2019-05-21 16:34:03] sent [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x585233b5> <pcomp> <accomp>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 46 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 46 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=24
[2019-05-21 16:34:03] ppp_start[0]: finished
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 54 bytes
[2019-05-21 16:34:03] pppos_input[0]: got 54 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] rcvd [LCP ConfReq id=0x0 <asyncmap 0x0> <auth 0xc223 05> <magic 0x40adf9c0>
                      <pcomp> <accomp>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:03] No auth is possible
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] sent [LCP ConfRej id=0x0 <auth 0xc223 05>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 24 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 24 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=13
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 46 bytes
[2019-05-21 16:34:03] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] rcvd [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x585233b5> <pcomp> <accomp>]
[2019-05-21 16:34:03] pppos_input[0]: got 46 bytes
[2019-05-21 16:34:03] rcvd [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x40adf9c0> <pcomp> <accomp>]
[2019-05-21 16:34:03] sent [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x40adf9c0> <pcomp> <accomp>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 44 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 44 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=24
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 21 bytes
[2019-05-21 16:34:03] netif_set_mtu[0]: mtu=1500
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] pppos_send_config[0]: out_accm=0 0 0 0
[2019-05-21 16:34:03] ppp_send_config[0]
[2019-05-21 16:34:03] pppos_recv_config[0]: in_accm=0 0 0 0
[2019-05-21 16:34:03] ppp_recv_config[0]
[2019-05-21 16:34:03] ppp phase changed[0]: phase=9
[2019-05-21 16:34:03] sent [IPCP ConfReq id=0x1 <addr 0.0.0.0> <ms-dns1 0.0.0.0> <ms-dns2 0.0.0.0>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 29 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 29 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=26
[2019-05-21 16:34:03] pppos_input[0]: got 21 bytes
[2019-05-21 16:34:03] rcvd [LCP DiscReq id=0x2 magic=0x40adf9c0]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 10 bytes
[2019-05-21 16:34:03] pppos_input[0]: got 10 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] rcvd [IPCP ConfReq id=0x0]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 28 bytes
[2019-05-21 16:34:03] sent [IPCP ConfNak id=0x0 <addr 0.0.0.0>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 17 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 17 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=14
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 10 bytes
[2019-05-21 16:34:03] pppos_input[0]: got 28 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] rcvd [IPCP ConfNak id=0x1 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-21 16:34:03] sent [IPCP ConfReq id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 29 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 29 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=26
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 28 bytes
[2019-05-21 16:34:03] pppos_input[0]: got 10 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:03] rcvd [IPCP ConfReq id=0x1]
[2019-05-21 16:34:03] sent [IPCP ConfAck id=0x1]
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 11 bytes
[2019-05-21 16:34:03] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 11 bytes
[2019-05-21 16:34:03] pppos_write[0]: len=8
[2019-05-21 16:34:03] pppos_input[0]: got 28 bytes
[2019-05-21 16:34:03] rcvd [IPCP ConfAck id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-21 16:34:03] Could not determine remote IP address: defaulting to 10.64.64.64
[2019-05-21 16:34:03] sifup[0]: err_code=0
[2019-05-21 16:34:03] PpposManager::pppLinkStatus: PPPERR_NONE
[2019-05-21 16:34:03]   ip4 = xxx.xxx.xxx.xxx
[2019-05-21 16:34:03]   gateway = 10.64.64.64
[2019-05-21 16:34:03]   netmask = 255.255.255.255
[2019-05-21 16:34:03]   dns1 = xxx.xxx.xxx.xxx
[2019-05-21 16:34:03]   dns2 = xxx.xxx.xxx.xxx
[2019-05-21 16:34:03] local  IP address xxx.xxx.xxx.xxx
[2019-05-21 16:34:03] remote IP address 10.64.64.64
[2019-05-21 16:34:03] primary   DNS address xxx.xxx.xxx.xxx
[2019-05-21 16:34:03] secondary DNS address xxx.xxx.xxx.xxx
[2019-05-21 16:34:03] ppp phase changed[0]: phase=10
[2019-05-21 16:34:07] HuaweiMe906::SerialPort(0x2004faf0)::backgroundProcess: received 29 bytes
[2019-05-21 16:34:07] PCUI port, read 25 bytes: "^HCSQ: "LTE",45,40,156,24"
[2019-05-21 16:34:07] HuaweiMe906::SerialPort(0x2004faf0)::requestRead: requesting 64 bytes
[2019-05-21 16:34:07] mqtt_client_connect: Connecting to host: 18.184.104.180 at port:1883
[2019-05-21 16:34:07] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 49 bytes
[2019-05-21 16:34:07] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 49 bytes
[2019-05-21 16:34:07] pppos_netif_output[0]: proto=0x21, len = 44
[2019-05-21 16:34:07] Connecting to MQTT broker...
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 49 bytes
[2019-05-21 16:34:08] pppos_input[0]: got 49 bytes
[2019-05-21 16:34:08] ppp_input[0]: ip in pbuf len=44
[2019-05-21 16:34:08] mqtt_tcp_connect_cb: TCP connection established to server
[2019-05-21 16:34:08] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 72, get 0,
                      put 72
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 53 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 53 bytes
[2019-05-21 16:34:08] pppos_netif_output[0]: proto=0x21, len = 112
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:08] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:08] ppp_input[0]: ip in pbuf len=40
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 49 bytes
[2019-05-21 16:34:08] pppos_input[0]: got 49 bytes
[2019-05-21 16:34:08] ppp_input[0]: ip in pbuf len=44
[2019-05-21 16:34:08] mqtt_parse_incoming: Remaining length after fixed header: 2
[2019-05-21 16:34:08] mqtt_parse_incoming: msg_idx: 4, cpy_len: 2, remaining 0
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:08] mqtt_message_received: Connect response code 0
[2019-05-21 16:34:08] mqttClientConnectionCallback: status = 0
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 44 bytes
[2019-05-21 16:34:08] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 44 bytes
[2019-05-21 16:34:08] pppos_netif_output[0]: proto=0x21, len = 40
[2019-05-21 16:34:12] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,32F746GDISCOVERY/online"
[2019-05-21 16:34:12] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 47, get 72,
                      put 119
[2019-05-21 16:34:12] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:12] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:12] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 28 bytes
[2019-05-21 16:34:12] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 28 bytes
[2019-05-21 16:34:12] pppos_netif_output[0]: proto=0x21, len = 87
[2019-05-21 16:34:12] mqtt_sub_unsub: Client (un)subscribe to topic
                      "distortos/0.7.0/ST,32F746GDISCOVERY/leds/+/state", id: 1
[2019-05-21 16:34:12] mqtt_output_send: tcp_sndbuf: 1025 bytes, ringbuf_linear_available: 55, get 119,
                      put 174
[2019-05-21 16:34:12] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state"
[2019-05-21 16:34:12] mqtt_output_send: tcp_sndbuf: 970 bytes, ringbuf_linear_available: 56, get 174,
                      put 230
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:13] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:13] ppp_input[0]: ip in pbuf len=40
[2019-05-21 16:34:13] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-05-21 16:34:13] mqttRequestCallback: error = 0
[2019-05-21 16:34:13] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-05-21 16:34:13] mqttRequestCallback: error = 0
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 28 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 28 bytes
[2019-05-21 16:34:13] pppos_netif_output[0]: proto=0x21, len = 151
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:13] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:13] ppp_input[0]: ip in pbuf len=40
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 50 bytes
[2019-05-21 16:34:13] pppos_input[0]: got 50 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:13] ppp_input[0]: ip in pbuf len=45
[2019-05-21 16:34:13] mqtt_parse_incoming: Remaining length after fixed header: 3
[2019-05-21 16:34:13] mqtt_parse_incoming: msg_idx: 5, cpy_len: 3, remaining 0
[2019-05-21 16:34:13] mqtt_message_received: SUBACK response with id 1
[2019-05-21 16:34:13] mqttRequestCallback: error = 0
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 45 bytes
[2019-05-21 16:34:13] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 45 bytes
[2019-05-21 16:34:13] pppos_netif_output[0]: proto=0x21, len = 40
[2019-05-21 16:34:23] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state"
[2019-05-21 16:34:23] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 26, get 230,
                      put 30
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 37 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 37 bytes
[2019-05-21 16:34:23] pppos_netif_output[0]: proto=0x21, len = 96
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:23] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:23] ppp_input[0]: ip in pbuf len=40
[2019-05-21 16:34:23] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-05-21 16:34:23] mqttRequestCallback: error = 0
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:23] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state"
[2019-05-21 16:34:23] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 56, get 30,
                      put 86
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 64 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 64 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 37 bytes
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 37 bytes
[2019-05-21 16:34:23] pppos_netif_output[0]: proto=0x21, len = 96
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 45 bytes
[2019-05-21 16:34:23] pppos_input[0]: got 45 bytes
[2019-05-21 16:34:23] ppp_input[0]: ip in pbuf len=40
[2019-05-21 16:34:23] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-05-21 16:34:23] mqttRequestCallback: error = 0
[2019-05-21 16:34:23] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:29] pppos_input[0]: got 64 bytes
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:29] pppos_input[0]: got 64 bytes
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:29] ppp_input[0]: ip in pbuf len=93
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:29] mqtt_parse_incoming: Remaining length after fixed header: 51
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:29] mqtt_parse_incoming: msg_idx: 53, cpy_len: 51, remaining 0
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:29] mqtt_incomming_publish: Received message with QoS 0 at topic:
                      distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state, payload length 1
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:29] mqttIncomingPublishCallback: topic =
                      "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state", total length = 1
[2019-05-21 16:34:29] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 38 bytes
[2019-05-21 16:34:30] mqttIncomingDataCallback: length = 1, flags = 1
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:30] pppos_input[0]: got 64 bytes
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 45 bytes
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 45 bytes
[2019-05-21 16:34:30] pppos_netif_output[0]: proto=0x21, len = 40
[2019-05-21 16:34:30] pppos_input[0]: got 64 bytes
[2019-05-21 16:34:30] ppp_input[0]: ip in pbuf len=93
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 44 bytes
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 44 bytes
[2019-05-21 16:34:30] pppos_netif_output[0]: proto=0x21, len = 40
[2019-05-21 16:34:30] pppos_input[0]: got 38 bytes
[2019-05-21 16:34:30] ppp_input[0]: ip in pbuf len=93
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 44 bytes
[2019-05-21 16:34:30] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 44 bytes
[2019-05-21 16:34:30] pppos_netif_output[0]: proto=0x21, len = 40
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 64 bytes
[2019-05-21 16:34:34] pppos_input[0]: got 64 bytes
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: received 34 bytes
[2019-05-21 16:34:34] pppos_input[0]: got 34 bytes
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::requestRead: requesting 64 bytes
[2019-05-21 16:34:34] ppp_input[0]: ip in pbuf len=93
[2019-05-21 16:34:34] mqtt_parse_incoming: Remaining length after fixed header: 51
[2019-05-21 16:34:34] mqtt_parse_incoming: msg_idx: 53, cpy_len: 51, remaining 0
[2019-05-21 16:34:34] mqtt_incomming_publish: Received message with QoS 0 at topic:
                      distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state, payload length 1
[2019-05-21 16:34:34] mqttIncomingPublishCallback: topic =
                      "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state", total length = 1
[2019-05-21 16:34:34] mqttIncomingDataCallback: length = 1, flags = 1
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::requestWrite: requesting 45 bytes
[2019-05-21 16:34:34] HuaweiMe906::SerialPort(0x2004fb5c)::backgroundProcess: transmitted 45 bytes
[2019-05-21 16:34:34] pppos_netif_output[0]: proto=0x21, len = 40
```
