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
