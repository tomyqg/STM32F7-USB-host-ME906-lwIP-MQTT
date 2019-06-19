STM32F7-USB-host-ME906-lwIP-MQTT [![Build Status](https://travis-ci.org/DISTORTEC/STM32F7-USB-host-ME906-lwIP-MQTT.svg)](https://travis-ci.org/DISTORTEC/STM32F7-USB-host-ME906-lwIP-MQTT)
================================

MQTT demo project for [32F746GDISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) (also known as
*STM32F746G-DISCO*) and [NUCLEO-F767ZI](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html) boards. It features
following components:
- *distortos*,
- *ST's* *STM32F7 HAL* and *USB host* libraries, with numerous fixes to make them actually usable,
- USB class driver for *Huawei ME906* modem,
- *lwIP*.

Configuration & building
------------------------

When you want to use *32F746GDISCOVERY* board:

    $ mkdir output
    $ cd output
    $ cmake -C../configurations/ST_32F746GDISCOVERY/distortosConfiguration.cmake .. -GNinja
    $ ninja

When you want to use *NUCLEO-F767ZI* board:

    $ mkdir output
    $ cd output
    $ cmake -C../configurations/ST_NUCLEO-F767ZI/distortosConfiguration.cmake .. -GNinja
    $ ninja

For more in-depth instructions see `distortos/README.md`.

MQTT
----

Once the modem connects to the network, it tries to connect to MQTT broker at `broker.hivemq.com`. When you subscribe to
the topic `distortos/#`, you should see the messages with device's online status (`1` is sent when the device connects,
`0` as a MQTT client's will once the connection is lost) and changes of button state.

With *32F746GDISCOVERY* board:

```
$ mosquitto_sub -h broker.hivemq.com -t "distortos/#" -v
distortos/0.7.0/ST,32F746GDISCOVERY/online 1
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 0
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 1
distortos/0.7.0/ST,32F746GDISCOVERY/buttons/0/state 0
```

With *NUCLEO-F767ZI* board:

```
$ mosquitto_sub -h broker.hivemq.com -t "distortos/#" -v
distortos/0.7.0/ST,NUCLEO-F767ZI/online 1
distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state 0
distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state 1
distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state 0
```

The application also allows you to control on-board LEDs via MQTT.

*32F746GDISCOVERY* board has just one LED available:

```
# set the LED on
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state" -m "1"
# set the LED off
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,32F746GDISCOVERY/leds/0/state" -m "0"
```

On *NUCLEO-F767ZI* board there are 3 LEDs:

```
# set green LED on
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/0/state" -m "1"
# set blue LED on
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/1/state" -m "1"
# set red LED on
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/2/state" -m "1"
# set green LED off
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/0/state" -m "0"
# set blue LED off
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/1/state" -m "0"
# set red LED off
$ mosquitto_pub -h broker.hivemq.com -t "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/2/state" -m "0"
```

Debug output
------------

ST-Link V2-1 has a virtual COM port which is used for debug output from the application. The stream uses typical
parameters: 115200 bps, 8N1. Below you will find the example of the output from *32F746GDISCOVERY* board.

```
[2019-06-19 14:40:53] Started ST,NUCLEO-F767ZI board
[2019-06-19 14:40:53] ppp phase changed[0]: phase=0
[2019-06-19 14:40:53] getaddrinfo() failed, ret = 202
[2019-06-19 14:40:53] PCUI port, read failed, errno = 128
[2019-06-19 14:40:53] GPS port, read failed, errno = 128
[2019-06-19 14:40:53] PpposManager::executeCommand: write failed, errno = 128
...
[2019-06-19 14:41:03] getaddrinfo() failed, ret = 202
[2019-06-19 14:41:03] PCUI port, read failed, errno = 128
[2019-06-19 14:41:03] GPS port, read failed, errno = 128
[2019-06-19 14:41:03] PpposManager::executeCommand: write failed, errno = 128
[2019-06-19 14:41:05] usbHostEventCallback: HOST_USER_CONNECTION
[2019-06-19 14:41:05] USB Device Attached
[2019-06-19 14:41:05] PID: 1573h
[2019-06-19 14:41:05] VID: 12d1h
[2019-06-19 14:41:05] Address (#1) assigned.
[2019-06-19 14:41:05] Manufacturer : HUAWEI Technology
[2019-06-19 14:41:05] Product : HUAWEI Mobile
[2019-06-19 14:41:06] Serial Number : ...
[2019-06-19 14:41:06] Enumeration done.
[2019-06-19 14:41:06] usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION
[2019-06-19 14:41:06] Default configuration set.
[2019-06-19 14:41:06] Device remote wakeup enabled
[2019-06-19 14:41:06] HuaweiMe906::SerialPort(0x2007faf0)::interfaceInitialize: interface 0,
                      read endpoint address 0x81, read endpoint size 64, read pipe 2,
                      write endpoint address 0x1, write endpoint size 64, write pipe 3
[2019-06-19 14:41:06] HuaweiMe906::SerialPort(0x2007fb5c)::interfaceInitialize: interface 2,
                      read endpoint address 0x83, read endpoint size 64, read pipe 4,
                      write endpoint address 0x3, write endpoint size 64, write pipe 5
[2019-06-19 14:41:06] HuaweiMe906::SerialPort(0x2007fbc8)::interfaceInitialize: interface 5,
                      read endpoint address 0x89, read endpoint size 64, read pipe 6,
                      write endpoint address 0x6, write endpoint size 64, write pipe 7
[2019-06-19 14:41:06] Huawei ME906 class started.
[2019-06-19 14:41:06] usbHostEventCallback: HOST_USER_CLASS_SELECTED
[2019-06-19 14:41:06] usbHostEventCallback: HOST_USER_CLASS_ACTIVE
[2019-06-19 14:41:08] getaddrinfo() failed, ret = 202
[2019-06-19 14:41:08] HuaweiMe906::SerialPort(0x2007faf0)::requestRead: requesting 64 bytes
[2019-06-19 14:41:08] HuaweiMe906::SerialPort(0x2007faf0)::backgroundProcess: received 29 bytes
[2019-06-19 14:41:08] HuaweiMe906::SerialPort(0x2007fbc8)::requestRead: requesting 64 bytes
[2019-06-19 14:41:08] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 5 bytes
[2019-06-19 14:41:08] PCUI port, read 25 bytes: "^HCSQ: "LTE",54,51,224,26"
[2019-06-19 14:41:08] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 5 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007faf0)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 5 bytes: "ATI"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 29 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 27 bytes: "^HCSQ: "LTE",54,51,224,26"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 45 bytes:
                      "Manufacturer: Huawei Technologies Co., Ltd."
[2019-06-19 14:41:09] PpposManager::executeCommand: read 15 bytes: "Model: ME906E"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 27 bytes: "Revision: 12.430.19.08.00"
[2019-06-19 14:41:09] PpposManager::executeCommand: read 23 bytes: "IMEI: ..."
[2019-06-19 14:41:09] PpposManager::executeCommand: read 14 bytes: "+GCAP: +CGSM"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 4 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 54 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 54 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 54 bytes:
                      "AT^SYSCFGEX="030201",3FFFFFFF,1,2,7FFFFFFFFFFFFFFF,,"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 6 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 11 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 11 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 11 bytes: "AT+COPS=0"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 6 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 44 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 44 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 44 bytes:
                      "AT+CGDCONT=1,"IP","internet","0.0.0.0",0,0"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 6 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 37 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 37 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 37 bytes:
                      "AT+CGDCONT=16,"IP","","0.0.0.0",0,0"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 6 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 12 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 12 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 12 bytes: "AT+CGATT=1"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 6 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 4 bytes: "OK"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 9 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 9 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: wrote 9 bytes: "ATD*99#"
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 21 bytes
[2019-06-19 14:41:09] PpposManager::executeCommand: read 19 bytes: "CONNECT 100000000"
[2019-06-19 14:41:09] ppp_connect[0]: holdoff=0
[2019-06-19 14:41:09] ppp phase changed[0]: phase=3
[2019-06-19 14:41:09] pppos_connect: unit 0: connecting
[2019-06-19 14:41:09] ppp_start[0]
[2019-06-19 14:41:09] ppp phase changed[0]: phase=6
[2019-06-19 14:41:09] pppos_send_config[0]: out_accm=FF FF FF FF
[2019-06-19 14:41:09] ppp_send_config[0]
[2019-06-19 14:41:09] pppos_recv_config[0]: in_accm=FF FF FF FF
[2019-06-19 14:41:09] ppp_recv_config[0]
[2019-06-19 14:41:09] sent [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x585233a9> <pcomp> <accomp>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=24
[2019-06-19 14:41:09] ppp_start[0]: finished
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 54 bytes
[2019-06-19 14:41:09] pppos_input[0]: got 54 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] rcvd [LCP ConfReq id=0x0 <asyncmap 0x0> <auth 0xc223 05> <magic 0x40adf8b6>
                      <pcomp> <accomp>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:09] No auth is possible
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] sent [LCP ConfRej id=0x0 <auth 0xc223 05>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 24 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 24 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=13
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:09] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] rcvd [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x585233a9> <pcomp> <accomp>]
[2019-06-19 14:41:09] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:09] rcvd [LCP ConfReq id=0x1 <asyncmap 0x0> <magic 0x40adf8b6> <pcomp> <accomp>]
[2019-06-19 14:41:09] sent [LCP ConfAck id=0x1 <asyncmap 0x0> <magic 0x40adf8b6> <pcomp> <accomp>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=24
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 22 bytes
[2019-06-19 14:41:09] netif_set_mtu[0]: mtu=1500
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] pppos_send_config[0]: out_accm=0 0 0 0
[2019-06-19 14:41:09] ppp_send_config[0]
[2019-06-19 14:41:09] pppos_recv_config[0]: in_accm=0 0 0 0
[2019-06-19 14:41:09] ppp_recv_config[0]
[2019-06-19 14:41:09] ppp phase changed[0]: phase=9
[2019-06-19 14:41:09] sent [IPCP ConfReq id=0x1 <addr 0.0.0.0> <ms-dns1 0.0.0.0> <ms-dns2 0.0.0.0>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 29 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 29 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=26
[2019-06-19 14:41:09] pppos_input[0]: got 22 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 10 bytes
[2019-06-19 14:41:09] rcvd [LCP DiscReq id=0x2 magic=0x40adf8b6]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] pppos_input[0]: got 10 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 28 bytes
[2019-06-19 14:41:09] rcvd [IPCP ConfReq id=0x0]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] sent [IPCP ConfNak id=0x0 <addr 0.0.0.0>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 17 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 17 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=14
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 10 bytes
[2019-06-19 14:41:09] pppos_input[0]: got 28 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] rcvd [IPCP ConfNak id=0x1 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-06-19 14:41:09] sent [IPCP ConfReq id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 29 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 29 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=26
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 28 bytes
[2019-06-19 14:41:09] pppos_input[0]: got 10 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:09] rcvd [IPCP ConfReq id=0x1]
[2019-06-19 14:41:09] sent [IPCP ConfAck id=0x1]
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 11 bytes
[2019-06-19 14:41:09] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 11 bytes
[2019-06-19 14:41:09] pppos_write[0]: len=8
[2019-06-19 14:41:09] pppos_input[0]: got 28 bytes
[2019-06-19 14:41:09] rcvd [IPCP ConfAck id=0x2 <addr xxx.xxx.xxx.xxx> <ms-dns1 xxx.xxx.xxx.xxx>
                      <ms-dns2 xxx.xxx.xxx.xxx>]
[2019-06-19 14:41:09] Could not determine remote IP address: defaulting to 10.64.64.64
[2019-06-19 14:41:09] sifup[0]: err_code=0
[2019-06-19 14:41:09] PpposManager::pppLinkStatus: PPPERR_NONE
[2019-06-19 14:41:09]   ip4 = xxx.xxx.xxx.xxx
[2019-06-19 14:41:09]   gateway = 10.64.64.64
[2019-06-19 14:41:09]   netmask = 255.255.255.255
[2019-06-19 14:41:09]   dns1 = xxx.xxx.xxx.xxx
[2019-06-19 14:41:09]   dns2 = xxx.xxx.xxx.xxx
[2019-06-19 14:41:09] local  IP address xxx.xxx.xxx.xxx
[2019-06-19 14:41:09] remote IP address 10.64.64.64
[2019-06-19 14:41:09] primary   DNS address xxx.xxx.xxx.xxx
[2019-06-19 14:41:09] secondary DNS address xxx.xxx.xxx.xxx
[2019-06-19 14:41:09] ppp phase changed[0]: phase=10
[2019-06-19 14:41:13] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:13] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:13] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 4 bytes
[2019-06-19 14:41:13] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 4 bytes
[2019-06-19 14:41:13] pppos_netif_output[0]: proto=0x21, len = 63
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:14] pppos_input[0]: got 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 36 bytes
[2019-06-19 14:41:14] pppos_input[0]: got 36 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:14] ppp_input[0]: ip in pbuf len=95
[2019-06-19 14:41:14] broker.hivemq.com is 35.157.173.121
[2019-06-19 14:41:14] mqtt_client_connect: Connecting to host: 35.157.173.121 at port:1883
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 49 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 49 bytes
[2019-06-19 14:41:14] pppos_netif_output[0]: proto=0x21, len = 44
[2019-06-19 14:41:14] Connecting to MQTT broker...
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 49 bytes
[2019-06-19 14:41:14] pppos_input[0]: got 49 bytes
[2019-06-19 14:41:14] ppp_input[0]: ip in pbuf len=44
[2019-06-19 14:41:14] mqtt_tcp_connect_cb: TCP connection established to server
[2019-06-19 14:41:14] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 69, get 0,
                      put 69
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 49 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 49 bytes
[2019-06-19 14:41:14] pppos_netif_output[0]: proto=0x21, len = 109
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:14] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:14] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 49 bytes
[2019-06-19 14:41:14] pppos_input[0]: got 49 bytes
[2019-06-19 14:41:14] ppp_input[0]: ip in pbuf len=44
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:14] mqtt_parse_incoming: Remaining length after fixed header: 2
[2019-06-19 14:41:14] mqtt_parse_incoming: msg_idx: 4, cpy_len: 2, remaining 0
[2019-06-19 14:41:14] mqtt_message_received: Connect response code 0
[2019-06-19 14:41:14] mqttClientConnectionCallback: status = 0
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:41:14] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:41:14] pppos_netif_output[0]: proto=0x21, len = 40
[2019-06-19 14:41:19] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/online"
[2019-06-19 14:41:19] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 44, get 69,
                      put 113
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 25 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 25 bytes
[2019-06-19 14:41:19] pppos_netif_output[0]: proto=0x21, len = 84
[2019-06-19 14:41:19] mqtt_sub_unsub: Client (un)subscribe to topic
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/+/state", id: 1
[2019-06-19 14:41:19] mqtt_output_send: tcp_sndbuf: 1028 bytes, ringbuf_linear_available: 52, get 113,
                      put 165
[2019-06-19 14:41:19] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state"
[2019-06-19 14:41:19] mqtt_output_send: tcp_sndbuf: 976 bytes, ringbuf_linear_available: 53, get 165,
                      put 218
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:19] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:19] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:41:19] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-06-19 14:41:19] mqttRequestCallback: error = 0
[2019-06-19 14:41:19] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-06-19 14:41:19] mqttRequestCallback: error = 0
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 22 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 22 bytes
[2019-06-19 14:41:19] pppos_netif_output[0]: proto=0x21, len = 145
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:19] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:19] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 51 bytes
[2019-06-19 14:41:19] pppos_input[0]: got 51 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:19] ppp_input[0]: ip in pbuf len=45
[2019-06-19 14:41:19] mqtt_parse_incoming: Remaining length after fixed header: 3
[2019-06-19 14:41:19] mqtt_parse_incoming: msg_idx: 5, cpy_len: 3, remaining 0
[2019-06-19 14:41:19] mqtt_message_received: SUBACK response with id 1
[2019-06-19 14:41:19] mqttRequestCallback: error = 0
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:41:19] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:41:19] pppos_netif_output[0]: proto=0x21, len = 40
[2019-06-19 14:41:25] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state"
[2019-06-19 14:41:25] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 38, get 218,
                      put 15
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 34 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 34 bytes
[2019-06-19 14:41:25] pppos_netif_output[0]: proto=0x21, len = 93
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 47 bytes
[2019-06-19 14:41:25] pppos_input[0]: got 47 bytes
[2019-06-19 14:41:25] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:41:25] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-06-19 14:41:25] mqttRequestCallback: error = 0
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:25] mqtt_publish: Publish with payload length 1 to topic
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/buttons/0/state"
[2019-06-19 14:41:25] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 53, get 15,
                      put 68
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 64 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 64 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 36 bytes
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 36 bytes
[2019-06-19 14:41:25] pppos_netif_output[0]: proto=0x21, len = 93
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 45 bytes
[2019-06-19 14:41:25] pppos_input[0]: got 45 bytes
[2019-06-19 14:41:25] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:41:25] mqtt_tcp_sent_cb: Calling QoS 0 publish complete callback
[2019-06-19 14:41:25] mqttRequestCallback: error = 0
[2019-06-19 14:41:25] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:32] pppos_input[0]: got 64 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 31 bytes
[2019-06-19 14:41:32] pppos_input[0]: got 31 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] ppp_input[0]: ip in pbuf len=90
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:32] mqtt_parse_incoming: Remaining length after fixed header: 48
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] mqtt_parse_incoming: msg_idx: 50, cpy_len: 48, remaining 0
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 31 bytes
[2019-06-19 14:41:32] mqtt_incomming_publish: Received message with QoS 0 at topic:
                      distortos/0.7.0/ST,NUCLEO-F767ZI/leds/0/state, payload length 1
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] mqttIncomingPublishCallback: topic =
                      "distortos/0.7.0/ST,NUCLEO-F767ZI/leds/0/state", total length = 1
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:41:32] mqttIncomingDataCallback: length = 1, flags = 1
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 31 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:41:32] pppos_netif_output[0]: proto=0x21, len = 40
[2019-06-19 14:41:32] pppos_input[0]: got 64 bytes
[2019-06-19 14:41:32] pppos_input[0]: got 31 bytes
[2019-06-19 14:41:32] ppp_input[0]: ip in pbuf len=90
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 44 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 44 bytes
[2019-06-19 14:41:32] pppos_netif_output[0]: proto=0x21, len = 40
[2019-06-19 14:41:32] pppos_input[0]: got 64 bytes
[2019-06-19 14:41:32] pppos_input[0]: got 31 bytes
[2019-06-19 14:41:32] ppp_input[0]: ip in pbuf len=90
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 44 bytes
[2019-06-19 14:41:32] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 44 bytes
[2019-06-19 14:41:32] pppos_netif_output[0]: proto=0x21, len = 40
[2019-06-19 14:42:29] mqtt_cyclic_timer: Sending keep-alive message to server
[2019-06-19 14:42:29] mqtt_output_send: tcp_sndbuf: 1072 bytes, ringbuf_linear_available: 2, get 68,
                      put 70
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 47 bytes
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 47 bytes
[2019-06-19 14:42:29] pppos_netif_output[0]: proto=0x21, len = 42
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 64 bytes
[2019-06-19 14:42:29] pppos_input[0]: got 64 bytes
[2019-06-19 14:42:29] ppp_input[0]: ip in pbuf len=40
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: received 28 bytes
[2019-06-19 14:42:29] pppos_input[0]: got 28 bytes
[2019-06-19 14:42:29] HuaweiMe906::SerialPort(0x2007fb5c)::requestRead: requesting 64 bytes
[2019-06-19 14:42:30] ppp_input[0]: ip in pbuf len=42
[2019-06-19 14:42:30] mqtt_parse_incoming: Remaining length after fixed header: 0
[2019-06-19 14:42:30] mqtt_message_received: Received PINGRESP from server
[2019-06-19 14:42:30] HuaweiMe906::SerialPort(0x2007fb5c)::requestWrite: requesting 45 bytes
[2019-06-19 14:42:30] HuaweiMe906::SerialPort(0x2007fb5c)::backgroundProcess: transmitted 45 bytes
[2019-06-19 14:42:30] pppos_netif_output[0]: proto=0x21, len = 40
```
