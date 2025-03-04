# Bitcoin_Martix_Scroller with cz news and fixed Bitcoin price 
 build from Marquee weather 2.13
## Marquee Scroller (Clock, Weather, News, and More)

## Features include:
* Accurate Clock refresh off Internet Time Servers
* Local Weather and conditions (refreshed every 10 - 30 minutes)
* News Headlines from all the major sources
* Configured through Web Interface
* Display 3D print progress from your OctoPrint Server
* Option to display Pi-hole status and graph (each pixel accross is 10 minutes)
* Basic Authorization around Configuration web interface
* Support for OTA (loading firmware over WiFi)
* Update firmware through web interface
* Configurable scroll speed
* Configurable scrolling frequency
* Configurable number of LED panels
* Options of different types of Clock Displays (display seconds or temperature) -- only on 8 or more display panels
* Video: https://youtu.be/DsThufRpoiQ
* Build Video by Chris Riley: https://youtu.be/KqBiqJT9_lE

## Required Parts:
* Wemos D1 Mini: https://amzn.to/3tMl81U
* Dot Matrix Module: https://amzn.to/2HtnQlD  

Note: Using the links provided here help to support these types of projects. Thank you for the support.  

## Wiring for the Wemos D1 Mini to the Dot Matrix Display
CLK -> D5 (SCK)  
CS  -> D6  
DIN -> D7 (MOSI)  
VCC -> 5V+  
GND -> GND-  

![Marquee Scroller Wiring](/images/marquee_scroller_pins.png)  

## 3D Printed Case by David Payne:  
Original Single Panel version: https://www.thingiverse.com/thing:2867294  
Double Wide LED version: https://www.thingiverse.com/thing:2989552  

## Upgrading from version 2.5 or Higher
In version 2.6 and higher, the binary files that can be uploaded to your marque scrolling clock via the web interface.  From the main menu in the web interface select "Firmware Update" and follow the prompts.
* **marquee.ino.d1_mini_3.01.bin** - compiled for Wemos D1 Mini and standard 4x1 LED (default)
* **marquee.ino.d1_mini_wide_3.01.bin** - compiled for Wemos D1 Mini and double wide 8x1 LED display

## Compiling and Loading to Wemos D1
It is recommended to use Arduino IDE.  You will need to configure Arduino IDE to work with the Wemos board and USB port and installed the required USB drivers etc.  
* USB CH340G drivers:  https://sparks.gogo.co.nz/ch340.html
* Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.  This will add support for the Wemos D1 Mini to Arduino IDE.
* Open Boards Manager from Tools > Board menu and install esp8266 Core platform version Latest **3.0.2**
* Select Board:  "ESP8266 Boards (3.0.2)" --> "LOLIN(WEMOS) D1 R2 & mini"
* Set Flash Size: 4MB (FS:1MB OTA:~1019KB) -- **this project requires FS for saving and reading configuration settings.**
* Select the **Port** from the tools menu.  

## Initial Configuration
Editing the **Settings.h** file is totally optional and not required.  All API Keys are now managed in the Web Interface. It is not required to edit the Settings.h file before loading and running the code.  
* Open Weather Map free API key: http://openweathermap.org/  -- this is used to get weather data and the latitude and longitude for the current time zone. Weather API key is required for correct time.
* TimeZoneDB free registration for API key: https://timezonedb.com/register -- this is used for setting the time and getting the correct time zone as well as managing time changes due to Day Light Savings time by regions.  This key is set and managed only through the web interface and added in version 2.10 of Marquee Scroller. TimeZoneDB key is required for correct time display.
* News API key (free): https://newsapi.org/ -- Optional if you want to get current news headlines.
* Your OctoPrint API Key -- optional if you use the OctoPrint status.
* Version 2.0 supports Chained 4x1 LED displays -- configure up to 16x1 in the Settings.h file.  

NOTE: The settings in the Settings.h are the default settings for the first loading. After loading you will manage changes to the settings via the Web Interface. If you want to change settings again in the settings.h, you will need to erase the file system on the Wemos or use the “Reset Settings” option in the Web Interface.  

## Web Interface
The Marquee Scroller uses the **WiFiManager** so when it can't find the last network it was connected to 
it will become a **AP Hotspot** -- connect to it with your phone and you can then enter your WiFi connection information.

After connected to your WiFi network it will display the IP addressed assigned to it and that can be 
used to open a browser to the Web Interface.  You will be able to manage your API Keys through the web interface.  
The default user / password for the configuration page is: admin / password  

The Clock will display the time of the City selected for the weather.  

<p align="center">
  <img src="/images/2018-04-19%2006.58.05.png" width="200"/>
  <img src="/images/2018-04-19%2006.58.15.png" width="200"/>
  <img src="/images/2018-04-19%2006.58.32.png" width="200"/>
  <img src="/images/2018-04-19%2006.58.58.png" width="200"/>
</p>

![Marquee Scroller](/images/5d7f02ccbf01125cabbf246f97f2ead1_preview_featured.jpg)  
![Marquee Parts](/images/1ffa0c835554d280258c13be5513c4fe_preview_featured.jpg)
