/*
 Name:		TICtoMQTT.ino
 Created:	03/04/2022 18:20:20
 Author:	renau
*/


void setup() {
	Serial.begin(9600);
	Serial2.begin(1200, SERIAL_7N1);
}

long i = 0;

// the loop function runs over and over again until power down or reset
void loop() {
  
	if (Serial2.available()) {
		Serial.print((char)Serial2.read());
	}
	/*
	i++;
	Serial.printf("Test \"Serial\" - %d\n", i);
	delay(500);
	*/

}
