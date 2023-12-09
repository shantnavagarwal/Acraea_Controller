# Acraea Control using an ESP32
Program to monitor and control the flow of seawater through [Acraea](https://codeberg.org/LibreWater/Acraea-Prototype). The main project files can be found inside "WaterLevelWebServer".

Acraea as introduced by LibreWater (Organisation that designe Acraea):
```
Acraea is a Small Scale Solar Desalination and Water Purification Prototype.
It is powered by electric heating for scientific purpose and for prototyping ahead according to the LibreWater Mission:

Providing Free and Open Source Hardware Designs for Solar-thermal Desalination that can be manufactured and innovated locally in Makerspaces across the world
```


## Implemented Functionality
- Sense the head of water in a container (of given length) using an ultrasonic sensor.
- Sense the temperature and humidity using an DHT20 sensor via I2C communication
- On/ Off control of a water pump to bring the head of the water to a desired value
- Logging data of the aforementioned parameters to onboard memory (CSV file) using SPIFFS
- Show information via a webserver running on this device allowing the user to see the aforementioned parameters, set desired water height and manually control the pump

![Images_ReadME/IMG_2929 2.PNG](https://github.com/shantnavagarwal/Acraea_Controller/blob/main/Images_ReadME/IMG_2929%202.PNG)
*Automatic control interface. User can specify the desired water level.*

![Images_ReadME/IMG_2930 2.PNG](https://github.com/shantnavagarwal/Acraea_Controller/blob/main/Images_ReadME/IMG_2930%202.PNG)
*Manual control interface. User can directly turn on/off the water pump.*

## List of materials required
- [ESP32](https://www.tinytronics.nl/shop/en/development-boards/microcontroller-boards/with-wi-fi/esp32-wifi-and-bluetooth-board-with-separate-headers-cp2104)
- [Ultrasonic Sensor](https://www.tinytronics.nl/shop/en/sensors/distance/ultrasonic-sensor-hc-sr04)
- [Temperature and Humidity Sensor](https://www.tinytronics.nl/shop/en/sensors/air/humidity/asair-dht20-temperature-and-humidity-sensor-i2c)
- [Water Pump](https://www.tinytronics.nl/shop/en/mechanics-and-actuators/motors/pumps/under-water-pump-vertical-3-6v)
- [Mechanical Relay](https://www.tinytronics.nl/shop/en/switches/relays/5v-relay-4-channel-high-active-or-low-active)
- Power supply

## Required Libraries
Following Libraries for the ESP32 are required
- [ESPAsyncWebSrv](https://github.com/dvarrel/ESPAsyncWebSrv)
- [DFRobot_DHT20](https://github.com/DFRobot/DFRobot_DHT20)

## Usage
- Flash the program on to the ESP32 using Arduino IDE after installing the aforementioned libraries.
- The ESP32 should be connected to the sensors (Ultrasonic, Temperature) and actuators (Relay). The respective pins have been specified at the beginning of the code.
- It is easier to use a breadboard/ power supply with multiple voltage and ground pins to make all the required connections.
- Once the program is flashed and ESP32 reboots, connect to WiFi with SSID "ESP32" and password "OpenHardware"
- Once connected to WiFi, go to webpage 192.168.4.1 - You should now be able to see the interface shown above.

## Issues & Feature improvements
- Data logging is not working right now. This needs to be debugged
- The sensor data is updated by refreshing the webpage every 5 seconds. We can improve this by using Javascript instead. This will reduce the load on the ESP32 and improve user experience.
- Allow user to set threshold and container depth through the webpage itself.
- Determine the optimal head of water given the current state of system.
- Make it modular and use OOP. Rewrite the code such that this functionality is available as a class with configurable pin numbers. This will allow a user to control multiple Acraea modules using a single ESP32. Optimize performance throught the already implemented FreeRTOS functionality by creating a separate process for each class object.
- Cloud based data logging. Might add costs for the user in terms of subscription fees.
- Push notifications using [Local push connectivity](https://developer.apple.com/documentation/networkextension/local_push_connectivity). Requires building a companion app but is a good to have feature.
- Functionality can be added to monitor the water quality as well! [TDS Sensor](https://www.tinytronics.nl/shop/en/sensors/liquid/dfrobot-gravity-analog-tds-sensor)
