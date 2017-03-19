# livarnoluxball-remote
Remote control for led light bulb using MySensors and IRlib to drive it remotely over MQTT and radio to IR signal

The Lamp was sold in LIDL Finland 2017 February. It has IR remote control with 16 buttons. I read the button values, and put them into code. This code now reads MySensors messages, and checks if the code is one of the values the light ball accepts, it will send it over IR and acknowledges it back to MySennsors. So it's rather dumb relay.

All the further logic and GUI is behind MySenors MQTT GW, and handled and visualized in OpenHab and Node-Red.

The program uses these libraries:
 * [IRLib2] (https://github.com/cyborg5/IRLib2)
 * [MySensors] (https://github.com/mysensors/MySensors)


Author: Ilkka Tengvall
LICENCE: GPLv3
