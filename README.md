STM32F7-USB-host-ME906-lwIP-MQTT
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

Debug output
------------

ST-Link V2-1 has a virtual COM port which is used for debug output from the application. The stream uses typical
parameters: 115200 bps, 8N1. Below you will find the example of the produced output.

```
[2019-05-14 14:39:24] Started ST,32F746GDISCOVERY board
[2019-05-14 14:39:24] ppp phase changed[0]: phase=0
[2019-05-14 14:39:24] PCUI port, read failed, errno = 128
[2019-05-14 14:39:24] GPS port, read failed, errno = 128
[2019-05-14 14:39:24] PpposManager::executeCommand: write failed, errno = 128
[2019-05-14 14:39:29] PCUI port, read failed, errno = 128
[2019-05-14 14:39:29] GPS port, read failed, errno = 128
[2019-05-14 14:39:29] PpposManager::executeCommand: write failed, errno = 128
[2019-05-14 14:39:34] PCUI port, read failed, errno = 128
[2019-05-14 14:39:34] GPS port, read failed, errno = 128
[2019-05-14 14:39:34] PpposManager::executeCommand: write failed, errno = 128
[2019-05-14 14:39:35] usbHostEventCallback: HOST_USER_CONNECTION
[2019-05-14 14:39:35] USB Device Attached
[2019-05-14 14:39:35] PID: 1573h
[2019-05-14 14:39:35] VID: 12d1h
[2019-05-14 14:39:35] Address (#1) assigned.
[2019-05-14 14:39:35] Manufacturer : HUAWEI Technology
[2019-05-14 14:39:35] Product : HUAWEI Mobile
[2019-05-14 14:39:35] Serial Number : ...
[2019-05-14 14:39:35] Enumeration done.
[2019-05-14 14:39:35] usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION
[2019-05-14 14:39:35] Default configuration set.
[2019-05-14 14:39:35] Device remote wakeup enabled
[2019-05-14 14:39:35] HuaweiMe906::SerialPort(0x2004fb00)::interfaceInitialize: interface 0, read endpoint address 0x81,
read endpoint size 64, read pipe 2, write endpoint address 0x1, write endpoint size 64, write pipe 3
[2019-05-14 14:39:35] HuaweiMe906::SerialPort(0x2004fb6c)::interfaceInitialize: interface 2, read endpoint address 0x83,
read endpoint size 64, read pipe 4, write endpoint address 0x3, write endpoint size 64, write pipe 5
[2019-05-14 14:39:35] HuaweiMe906::SerialPort(0x2004fbd8)::interfaceInitialize: interface 5, read endpoint address 0x89,
read endpoint size 64, read pipe 6, write endpoint address 0x6, write endpoint size 64, write pipe 7
[2019-05-14 14:39:35] Huawei ME906 class started.
[2019-05-14 14:39:35] usbHostEventCallback: HOST_USER_CLASS_SELECTED
[2019-05-14 14:39:35] usbHostEventCallback: HOST_USER_CLASS_ACTIVE
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb00)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb00)::backgroundProcess: received 29 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fbd8)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 5 bytes
[2019-05-14 14:39:39] PCUI port, read 25 bytes: "^HCSQ: "LTE",57,55,127,24"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 5 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb00)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 5 bytes: "ATI"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 29 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 27 bytes: "^HCSQ: "LTE",57,55,127,24"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 64 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 45 bytes: "Manufacturer: Huawei Technologies Co., Ltd."
[2019-05-14 14:39:39] PpposManager::executeCommand: read 15 bytes: "Model: ME906E"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 64 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 27 bytes: "Revision: 12.430.19.08.00"
[2019-05-14 14:39:39] PpposManager::executeCommand: read 23 bytes: "IMEI: ..."
[2019-05-14 14:39:39] PpposManager::executeCommand: read 14 bytes: "+GCAP: +CGSM"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 4 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 54 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 54 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 54 bytes: "AT^SYSCFGEX="030201",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 6 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 11 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 11 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 11 bytes: "AT+COPS=0"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 6 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 44 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 44 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 44 bytes: "AT+CGDCONT=1,"IP","internet","0.0.0.0",0,0"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 6 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 37 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 37 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 37 bytes: "AT+CGDCONT=16,"IP","","0.0.0.0",0,0"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 6 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 12 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 12 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 12 bytes: "AT+CGATT=1"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 6 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 9 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 9 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: wrote 9 bytes: "ATD*99#"
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 21 bytes
[2019-05-14 14:39:39] PpposManager::executeCommand: read 19 bytes: "CONNECT 100000000"
[2019-05-14 14:39:39] ppp_connect[0]: holdoff=0
[2019-05-14 14:39:39] ppp phase changed[0]: phase=3
[2019-05-14 14:39:39] pppos_connect: unit 0: connecting
[2019-05-14 14:39:39] ppp_start[0]
[2019-05-14 14:39:39] ppp phase changed[0]: phase=6
[2019-05-14 14:39:39] pppos_send_config[0]: out_accm=FF FF FF FF
[2019-05-14 14:39:39] ppp_send_config[0]
[2019-05-14 14:39:39] pppos_recv_config[0]: in_accm=FF FF FF FF
[2019-05-14 14:39:39] ppp_recv_config[0]
[2019-05-14 14:39:39] sent [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x585233a6> <pcomp> <accomp>]
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 45 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 45 bytes
[2019-05-14 14:39:39] pppos_write[0]: len=24
[2019-05-14 14:39:39] ppp_start[0]: finished
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 54 bytes
[2019-05-14 14:39:39] pppos_input[0]: got 54 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] rcvd [LCP ConfReq id=0x0 <asyncmap 0x0> <auth 0xc223 05> <magic 0x40adf9b3> <pcomp> <accomp>]
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 45 bytes
[2019-05-14 14:39:39] No auth is possible
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] sent [LCP ConfRej id=0x0 <auth 0xc223 05>]
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 24 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 24 bytes
[2019-05-14 14:39:39] pppos_write[0]: len=13
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 46 bytes
[2019-05-14 14:39:39] pppos_input[0]: got 45 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:39] rcvd [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x585233a6> <pcomp> <accomp>]
[2019-05-14 14:39:39] pppos_input[0]: got 46 bytes
[2019-05-14 14:39:39] rcvd [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x40adf9b3> <pcomp> <accomp>]
[2019-05-14 14:39:39] sent [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x40adf9b3> <pcomp> <accomp>]
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 44 bytes
[2019-05-14 14:39:39] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 44 bytes
[2019-05-14 14:39:40] pppos_write[0]: len=24
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 21 bytes
[2019-05-14 14:39:40] netif_set_mtu[0]: mtu=1500
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:40] pppos_send_config[0]: out_accm=0 0 0 0
[2019-05-14 14:39:40] ppp_send_config[0]
[2019-05-14 14:39:40] pppos_recv_config[0]: in_accm=0 0 0 0
[2019-05-14 14:39:40] ppp_recv_config[0]
[2019-05-14 14:39:40] ppp phase changed[0]: phase=9
[2019-05-14 14:39:40] sent [IPCP ConfReq id=0x1 <addr 0.0.0.0> <ms-dns1 0.0.0.0> <ms-dns2 0.0.0.0>]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 29 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 29 bytes
[2019-05-14 14:39:40] pppos_write[0]: len=26
[2019-05-14 14:39:40] pppos_input[0]: got 21 bytes
[2019-05-14 14:39:40] rcvd [LCP DiscReq id=0x2 magic=0x40adf9b3]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 10 bytes
[2019-05-14 14:39:40] pppos_input[0]: got 10 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:40] rcvd [IPCP ConfReq id=0x0]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 28 bytes
[2019-05-14 14:39:40] sent [IPCP ConfNak id=0x0 <addr 0.0.0.0>]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 17 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 17 bytes
[2019-05-14 14:39:40] pppos_write[0]: len=14
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 10 bytes
[2019-05-14 14:39:40] pppos_input[0]: got 28 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:40] rcvd [IPCP ConfNak id=0x1 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx> <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-14 14:39:40] sent [IPCP ConfReq id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx> <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 29 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 29 bytes
[2019-05-14 14:39:40] pppos_write[0]: len=26
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: received 28 bytes
[2019-05-14 14:39:40] pppos_input[0]: got 10 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestRead: requesting 64 bytes
[2019-05-14 14:39:40] rcvd [IPCP ConfReq id=0x1]
[2019-05-14 14:39:40] sent [IPCP ConfAck id=0x1]
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::requestWrite: requesting 11 bytes
[2019-05-14 14:39:40] HuaweiMe906::SerialPort(0x2004fb6c)::backgroundProcess: transmitted 11 bytes
[2019-05-14 14:39:40] pppos_write[0]: len=8
[2019-05-14 14:39:40] pppos_input[0]: got 28 bytes
[2019-05-14 14:39:40] rcvd [IPCP ConfAck id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx> <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-05-14 14:39:40] Could not determine remote IP address: defaulting to 10.64.64.64
[2019-05-14 14:39:40] sifup[0]: err_code=0
[2019-05-14 14:39:40] PpposManager::pppLinkStatus: PPPERR_NONE
[2019-05-14 14:39:40]   ip4 = xxx.xxx.xxx.xxx
[2019-05-14 14:39:40]   gateway = 10.64.64.64
[2019-05-14 14:39:40]   netmask = 255.255.255.255
[2019-05-14 14:39:40]   dns1 = xxx.xxx.xxx.xxx
[2019-05-14 14:39:40]   dns2 = xxx.xxx.xxx.xxx
[2019-05-14 14:39:40] local  IP address xxx.xxx.xxx.xxx
[2019-05-14 14:39:40] remote IP address 10.64.64.64
[2019-05-14 14:39:40] primary   DNS address xxx.xxx.xxx.xxx
[2019-05-14 14:39:40] secondary DNS address xxx.xxx.xxx.xxx
[2019-05-14 14:39:40] ppp phase changed[0]: phase=10
```
