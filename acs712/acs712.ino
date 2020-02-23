//#include <SoftwareSerial.h> //used to create custom serial ports
//#include <ArduinoJson.h>
//SoftwareSerial s(5,6);// Rx,Tx

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//#include <<span class="TextRun Highlight BCX0 SCXW174472232" lang="EN-US" xml:lang="EN-US" data-contrast="auto"><span class="SpellingError BCX0 SCXW174472232">FirebaseArduino.h></span></span>
#define FIREBASE_HOST "bhms-f93ab.firebaseio.com"
#define FIREBASE_AUTH "0Osowul7cfKPABr6003aYDKqlYEkYMOrCoo7MlW9"
#define WIFI_SSID "Laxus"
#define WIFI_PASSWORD "qwerty123567"

void setup() {
  Serial.begin(9600);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


double Voltage = 0;
double Current = 0;
float tempCel =0;
int temp;
//void setup(){
//Serial.begin(9600);
//s.begin(9600);
//}

void loop(){

// Voltage is Sensed 1000 Times for precision
for(int i = 0; i < 1000; i++) {
  Voltage = (Voltage + (0.0049 * analogRead(A0))); // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
  delay(10);
}
//lm35 calc
//temp = analogRead(A1);
//tempCel = (temp/1024.0)*500;

Voltage = Voltage /1000;
Current = (Voltage -2.5)/ 0.185; // Sensed voltage is converter to current

//Serial.print("\nSurface temperature in degree celcius: 0");
//Serial.print(tempCel);
//Serial.print("*C |");

Serial.print("\n Voltage Sensed (V) = "); // shows the measured voltage
Serial.print(Voltage,5); // the '2' after voltage allows you to display 2 digits after decimal point
Serial.print("\t Current (A) = "); // shows the voltage measured
Serial.print(Current,5); // the '2' after voltage allows you to display 2 digits after decimal point

Firebase.setFloat("voltage", Voltage);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting voltage failed:");
      Serial.println(Firebase.error());  
      return;
  }

  Firebase.setFloat("current", Current);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting voltage failed:");
      Serial.println(Firebase.error());  
      return;
  }

  //Firebase.setFloat("surface_temp", tempCel);
  // handle error
  //if (Firebase.failed()) {
   //   Serial.print("setting voltage failed:");
   //   Serial.println(Firebase.error());  
     // return;
 // }

//serial comm b/w arduino and nodemcu

//StaticJsonBuffer<5000> jsonBuffer;;
//JsonObject& data = jsonBuffer.createObject();
//data["Voltage"] = Voltage;
//data["Current"] = Current;
//data["tempCel"] = tempCel;
//if(s.available()>0){
//  data.printTo(s);
//}
//till here serial comm
delay(1000);

}
