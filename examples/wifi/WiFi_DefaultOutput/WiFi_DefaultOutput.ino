/*
 MIT License

Copyright (c) 2019 Phil Bowles <esparto8266@gmail.com>
                      blog     https://8266iot.blogspot.com     
                support group  https://www.facebook.com/groups/esp8266questions/
                
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <ESPArto.h>
//
//  Demonstrates the DefaultOutput feature of Esparto
//
//    Many IOT devices have a simple switching function on or off. The DefaultOutput pin will be switched
//    when any of the following occur:
//
//    a) Short-press of a std3Stage button (if no other function defined)
//    b) a "switch" command with a payload or 0 or 1 is received via:
//        i)    web UI run panel
//        ii)   web REST call to http://< IP>/switch/1 or  http://< IP>/switch/1
//        iii)  MQTT topic <this device>/switch with payload of 0 or 1
//        iv)   MQTT topic all/switch with payload of 0 or 1
//        v)    User calling invokeCmd("switch", ... payload 0 / 1 from code
//    c) voice command "Alexa! Turn on <your device name>" / "Alexa! Turn off <your device name>"
//
//  NB the notion of "ON" and "OFF" depend on the setting of the "Active" parameter
//  in the common case of active HIGH (i.e. a voltage on the output causes the desired action)
//  conceptual "ON" (Alexa switch "on", payload=1 in any of the above scenarios) is the same as HIGH
//  for systems with active LOW status (e.g many built-in LEDs) ON is equivalent to LOW
//
//  The DefaultOutput pin may optionally call a function after the default action to allow additional
//  behaviour e.g. toggling LED after switching a relay to show its ON. see (SONOFF firmware example)
//
//  **************************************************************************************************
//  *
//  *                      NB YOU MUST UPLOAD SPIFFS DATA BEFORE RUNNING THIS SKETCH! 
//  *                      use Tools/ESP8266 Sketch Data Upload 
//  *    
//  *                         When compiling for 1M devices use 64k SPIFFS
//  *                         When compiling for 4M devices use 1M SPIFFS
//  *
//  **************************************************************************************************             
//
//  This example included for completeness: functionality limited by lack of MQTT but will respond to all
//  scenarios above except b) iii) and b) iv)
// 
const char* yourSSID="LaPique";
const char* yourPWD="";
const char* yourDevice="testbed";

ESPArto Esparto(yourSSID,yourPWD,yourDevice);
//
//  What we want Alexa to know us as:
//
const char*  setAlexaDeviceName(){ return "salon kitty";  }

void onWiFiConnect(){
  // these messages with the IP address in them cannot be put in setupHarware() as the WiFi
  // may not have connected by then! This is the ONLY logical place for them
  Serial.printf("browse to either http://%s.local or http://%s an use run panel to execute cmd/switch payload=0 or 1\n",yourDevice,THIS_IP);
  Serial.printf(" or try  REST-like web call: http://%s/switch/0 or http://%s/switch/1\n",THIS_IP,THIS_IP);
  Serial.printf(" or use MQTT client to publish %s/switch or all/switch with payload=0 or 1\n",yourDevice);
}

void setupHardware(){
  Serial.begin(74880); 
  Serial.printf("Esparto WiFi DefaultOutput example %s\n",__FILE__);
  Esparto.DefaultOutput(); // defaults: BUILTIN_LED, active=LOW, initial=HIGH, no additional function
  Esparto.std3StageButton();
  Serial.printf("Short press on GPIO0 will toggle LED\n");
}
