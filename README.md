STM32F7-USB-host-ME906-lwIP-MQTT
================================

MQTT demo project for [32F746GDISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) board, also known
as *STM32F746G-DISCO*. It features following components:
- *distortos*,
- *ST's* *USB host* and *STM32F7 HAL* libraries, with numerous fixes to make them actually usable,
- USB class driver for *Huawei ME906* modem (WIP),
- *lwIP* (WIP).

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
[2019-04-30 12:27:24] Started ST,32F746GDISCOVERY board
[2019-04-30 12:27:25] PCUI port, read failed, errno = 128
[2019-04-30 12:27:25] Network card port, read failed, errno = 128
[2019-04-30 12:27:25] GPS port, read failed, errno = 128
[2019-04-30 12:27:25] PCUI port, write failed, errno = 128
[2019-04-30 12:27:25] Network card port, write failed, errno = 128
[2019-04-30 12:27:25] GPS port, write failed, errno = 128
[2019-04-30 12:27:30] PCUI port, read failed, errno = 128
[2019-04-30 12:27:30] Network card port, read failed, errno = 128
[2019-04-30 12:27:30] GPS port, read failed, errno = 128
[2019-04-30 12:27:30] PCUI port, write failed, errno = 128
[2019-04-30 12:27:30] Network card port, write failed, errno = 128
[2019-04-30 12:27:30] GPS port, write failed, errno = 128
...
[2019-04-30 12:27:46] usbHostEventCallback: HOST_USER_CONNECTION
[2019-04-30 12:27:46] USB Device Attached
[2019-04-30 12:27:46] PID: 1573h
[2019-04-30 12:27:46] VID: 12d1h
[2019-04-30 12:27:46] Address (#1) assigned.
[2019-04-30 12:27:46] Manufacturer : HUAWEI Technology
[2019-04-30 12:27:46] Product : HUAWEI Mobile
[2019-04-30 12:27:46] Serial Number : ...
[2019-04-30 12:27:46] Enumeration done.
[2019-04-30 12:27:46] usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION
[2019-04-30 12:27:46] Default configuration set.
[2019-04-30 12:27:46] Device remote wakeup enabled
[2019-04-30 12:27:46] HuaweiMe906::SerialPort(0x2004fa98)::interfaceInitialize: interface 0, read endpoint address 0x81,
read endpoint size 64, read pipe 2, write endpoint address 0x1, write endpoint size 64, write pipe 3
[2019-04-30 12:27:46] HuaweiMe906::SerialPort(0x2004fb04)::interfaceInitialize: interface 2, read endpoint address 0x83,
read endpoint size 64, read pipe 4, write endpoint address 0x3, write endpoint size 64, write pipe 5
[2019-04-30 12:27:46] HuaweiMe906::SerialPort(0x2004fb70)::interfaceInitialize: interface 5, read endpoint address 0x89,
read endpoint size 64, read pipe 6, write endpoint address 0x6, write endpoint size 64, write pipe 7
[2019-04-30 12:27:46] Huawei ME906 class started.
[2019-04-30 12:27:46] usbHostEventCallback: HOST_USER_CLASS_SELECTED
[2019-04-30 12:27:46] usbHostEventCallback: HOST_USER_CLASS_ACTIVE
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 29 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::backgroundProcess: received 29 bytes
[2019-04-30 12:27:50] PCUI port, read 25 bytes: "^HCSQ: "LTE",59,55,105,20"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] Network card port, read 25 bytes: "^HCSQ: "LTE",59,55,105,20"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::requestWrite: requesting 13 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestWrite: requesting 5 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::requestWrite: requesting 10 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: transmitted 5 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:50] PCUI port, wrote 5 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::backgroundProcess: transmitted 10 bytes
[2019-04-30 12:27:50] PCUI port, read 43 bytes: "Manufacturer: Huawei Technologies Co., Ltd."
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:50] Network card port, wrote 10 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: transmitted 13 bytes
[2019-04-30 12:27:50] PCUI port, read 13 bytes: "Model: ME906E"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::backgroundProcess: received 29 bytes
[2019-04-30 12:27:50] GPS port, read 41 bytes: "+CGDCONT: 1,"IP","internet","0.0.0.0",0,0"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] GPS port, wrote 13 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] Network card port, read 19 bytes: "+COPS: 0,0,"PLAY",7"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:50] Network card port, read 2 bytes: "OK"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: received 23 bytes
[2019-04-30 12:27:50] PCUI port, read 25 bytes: "Revision: 12.430.19.08.00"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb04)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] GPS port, read 34 bytes: "+CGDCONT: 16,"IP","","0.0.0.0",0,0"
[2019-04-30 12:27:50] PCUI port, read 21 bytes: "IMEI: ..."
[2019-04-30 12:27:50] GPS port, read 2 bytes: "OK"
[2019-04-30 12:27:50] PCUI port, read 12 bytes: "+GCAP: +CGSM"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fb70)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 4 bytes
[2019-04-30 12:27:50] PCUI port, read 2 bytes: "OK"
[2019-04-30 12:27:50] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::requestWrite: requesting 5 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: transmitted 5 bytes
[2019-04-30 12:27:52] PCUI port, wrote 5 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:52] PCUI port, read 43 bytes: "Manufacturer: Huawei Technologies Co., Ltd."
[2019-04-30 12:27:52] PCUI port, read 13 bytes: "Model: ME906E"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb04)::requestWrite: requesting 10 bytes
[2019-04-30 12:27:52] PCUI port, read 25 bytes: "Revision: 12.430.19.08.00"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb04)::backgroundProcess: transmitted 10 bytes
[2019-04-30 12:27:52] PCUI port, read 21 bytes: "IMEI: ..."
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb04)::backgroundProcess: received 29 bytes
[2019-04-30 12:27:52] Network card port, wrote 10 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::requestWrite: requesting 13 bytes
[2019-04-30 12:27:52] PCUI port, read 12 bytes: "+GCAP: +CGSM"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: transmitted 13 bytes
[2019-04-30 12:27:52] Network card port, read 19 bytes: "+COPS: 0,0,"PLAY",7"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] GPS port, wrote 13 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: received 4 bytes
[2019-04-30 12:27:52] Network card port, read 2 bytes: "OK"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: received 64 bytes
[2019-04-30 12:27:52] PCUI port, read 2 bytes: "OK"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb04)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] GPS port, read 41 bytes: "+CGDCONT: 1,"IP","internet","0.0.0.0",0,0"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fa98)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::requestRead: requesting 64 bytes
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::backgroundProcess: received 23 bytes
[2019-04-30 12:27:52] GPS port, read 34 bytes: "+CGDCONT: 16,"IP","","0.0.0.0",0,0"
[2019-04-30 12:27:52] GPS port, read 2 bytes: "OK"
[2019-04-30 12:27:52] HuaweiMe906::SerialPort(0x2004fb70)::requestRead: requesting 64 bytes
[2019-04-30 12:27:54] HuaweiMe906::SerialPort(0x2004fa98)::requestWrite: requesting 5 bytes
[2019-04-30 12:27:54] HuaweiMe906::SerialPort(0x2004fa98)::backgroundProcess: transmitted 5 bytes
...
```
