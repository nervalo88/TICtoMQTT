/*
 Name:		TICtoMQTT.ino
 Created:	03/04/2022 18:20:20
 Author:	renau
*/



#include <WiFi.h>   
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <strings_en.h>


String data;
String ppap;
String base;

int ppapVal;
long baseVal;

WiFiManager wifiManager;



void setup() {
	Serial.begin(9600);
	Serial2.begin(1200, SERIAL_7N1);
	wifiManager.autoConnect("TICtoMQTT");

}

long i = 0;

// the loop function runs over and over again until power down or reset
void loop() {
  
	if (Serial2.available()) {

		data = Serial2.readStringUntil('\n');
		if (data.startsWith("PAPP")) { 
			ppap = data.substring(5,10);
			ppapVal = ppap.toInt();
			Serial.print("Power: ");
			Serial.println(ppapVal);
		}
		if (data.startsWith("BASE")) {
			base = data.substring(5,14);
			baseVal = base.toInt();
			Serial.print("base:");
			Serial.println(baseVal);
		}

	}
}