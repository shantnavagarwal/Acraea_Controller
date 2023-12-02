# Acraea Control using an ESP32

### Features
- Web page served via a webserver running on esp32 to see the current water level, temprature, humidity and whether the water pump is on / off<br>
- Allows user to set the pump in manual or automatic mode. <br>
- In automatic mode, the target water level can be set on the webpage and the pump will automatically turn on if it is below that level.<br>
- In manual mode the user can control the pump manually through the webpage.<br>
- All the data is logged periodically into an CSV file stored in the onboard memory using SPIFFS.<br>
- Processing is distributed across both the cores of the ESP32<br>


### To be done
- Proper documentation and comments within the code <br>
- Refrences to libraries and contributors who provided inspiration for this solution <br>
- Data logging is not working right now. This needs to be debugged<br>
- Functionality can be added to monitor the water quality as well!<br>

