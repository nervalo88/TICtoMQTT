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
WiFiManager wifiManager;
#include <PubSubClient.h>

WiFiClient espCLient;
PubSubClient client(espCLient);

#include "Secret.h"

#define STATUSLED_TIC 5
bool ticState;
#define STATUSLED_WIFI 26 

String data;
String ppap;
String base;


char ppapVal[5];
char baseVal[9];

long lastMsg = 0;


void setup() {
	Serial.begin(9600);
	Serial2.begin(1200, SERIAL_7N1);
	wifiManager.autoConnect("TICtoMQTT");

	client.setServer(mqtt_server, 1883);
	//client.setCallback(callback); //NOT NEEDED : no input
	pinMode(STATUSLED_TIC, OUTPUT);
	pinMode(STATUSLED_WIFI, OUTPUT);

	digitalWrite(STATUSLED_WIFI, false);
	if(WiFi.status() == WL_CONNECTED) digitalWrite(STATUSLED_WIFI, true);



}

long i = 0;

// the loop function runs over and over again until power down or reset
void loop() {
	if (!client.connected()) {
		digitalWrite(STATUSLED_WIFI, false);
		reconnect();
	}
	client.loop();

	/*long now = millis();
	if (now - lastMsg > 500) {
		lastMsg = now;
		
		digitalWrite(STATUSLED_WIFI, !ticState);
		
	}*/
		if (Serial2.available()) {

			data = Serial2.readStringUntil('\n');
			if (data.startsWith("PAPP")) {
				ppap = data.substring(5, 10);
				strcpy(ppapVal, ppap.c_str());

				client.publish("espTIC/ppap", ppapVal, 1);

				Serial.print("Power: ");
				Serial.println(ppapVal);
			}
			if (data.startsWith("BASE")) {
				base = data.substring(5, 14);
				strcpy(baseVal, base.c_str());
				client.publish("espTIC/base", baseVal, 1);
				Serial.print("base:");
				Serial.println(baseVal);
				digitalWrite(STATUSLED_TIC, ticState);
				ticState = !ticState;
				
			}

		}
	//}
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect("EspTICClient")) {
			Serial.println("connected");
			digitalWrite(STATUSLED_WIFI, true);
			// Subscribe
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}