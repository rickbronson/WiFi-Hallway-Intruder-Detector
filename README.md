  WiFi Hallway Intruder Detector
==========================================

  This fun project takes a WiFi chip and ties it to a PIR
	(Pyroelectric Infrared Sensor) module for detecting human movement
	that is accessible on WiFi.

1. The Challenge
--------------

  Learn about PIR detection and the esp8266 WiFi module and how to
	connect them up.  Play around with the two settings on the PIR
	module, see below for image of PIR module.

2. Hardware Design
--------------
 
  The PIR module has just one output, it goes high when the module
	detects movement.  This gets feed into the esp8266 Rx pin (GPIO3).
	GPIO2 is used to turn on an LED to show movement.  I tried using the
	3.3 volt regulator on the PIR board for the esp8266 but that causes
	the PIR board to always think there is movement so I put a separate
	3.3 volt regulator on.  A button is tied from GPIO0 to ground to
	reset the WiFi module back to AP+STA (both Access Point and Station
	modes) so that you can then go to 192.168.4.1 and set it up to
	attach to your local network (ie. your router).

3. Software Design
--------------

  I started with the very simple and well written
	http://git.spritesserver.nl/esphttpd.git/ and changed it ever so
	slightly.  Clicking on the LED ON button changes the meaning of the
	LED such that the LED stays on normally but goes off to show
	movement.  When the AP button (see above) is pressed for more than 5
	seconds then the WiFi goes to AP+STA (both Access Point and Station
	modes).  On your computer or phone, scan for WiFi hotspots and
	something like "ESP_02F89B" should show up, connect to it then open
	a browser to 192.168.4.1 and set it up.  Click on the end of "If you
	haven't connected this device to your WLAN network now, you can do
	so." and then select your wireless router, enter your password.  It
	will tell you the IP address that it got, write that down.  Now
	connect back up to your home router and go to that IP address with a
	browser, you should see the same page that you saw at 192.168.4.1.

4. Parts
--------------
  I had many of the parts but here are some that I ordered:

[FTDI-USB](http://www.aliexpress.com/item/1pcs-FT232RL-FTDI-USB-3-3V-5-5V-to-TTL-Serial-Adapter-Module-for-Arduino-Mini/2019421866.html)

[LM1117](http://www.aliexpress.com/item/Free-Shipping-10PCS-LOT-Original-AMS1117-3-3V-AMS1117-LM1117-Voltage-Regulator-We-only-provide-good/32452410702.html)

[ESP8266](http://www.aliexpress.com/item/Free-Shipping-ESP8266-remote-serial-Port-WIFI-wireless-module-through-walls-Wang/2038068522.html)

[PIR Module](http://www.aliexpress.com/item/Hot-Sale-Adjust-IR-Pyroelectric-Infrared-IR-PIR-Motion-Sensor-Detector-Module-HC-SR501/32254718685.html)

[Blank PCB](http://www.aliexpress.com/item/New-Double-Side-Prototype-PCB-Tinned-Universal-Breadboard-3x7cm-30mmx70mm-hot-selling/32457220375.html)

5. Tools
--------------

  Debian Linux was used to build using
  https://github.com/pfalcon/esp-open-sdk.  Here is a rough guide to
  build everything.

```
sudo apt-get install libtool-bin gperf
mkdir -p ~/boards/esp8266
cd ~/boards/esp8266
git clone https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector.git
git clone https://github.com/pfalcon/esp-open-sdk
cd esp-open-sdk; make
cd ../WiFi-Hallway-Intruder-Detector; make
```

  I had to change esp-open-sdk/esptool/esptool.py because of serial
comm trouble:

```
!     ESP_RAM_BLOCK = 0x180
!     ESP_FLASH_BLOCK = 0x40 
```

5. Images
--------------

A picture of the detector.
![alt text](https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector/blob/master/images/photo.jpg "detector")
Schematic
![alt text](https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector/blob/master/images/schematic.jpg "schematic")
PIR Module adjustment
![alt text](https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector/blob/master/html/images/pir-adjustment.jpg "pir-adjustment")
Photo of ESP8266 Module
![alt text](https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector/blob/master/html/images/wifi-pic.jpg "wifi-pic")
PIR Sensor info
[PIR Sensor PDF](https://github.com/rickbronson/WiFi-Hallway-Intruder-Detector/blob/master/html/images/PIR-RE200B.pdf)
