#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
int data;
float voltage = 0;
float current = 0;
float percentSOC = 0;

#define FIREBASE_HOST "https://bhms-parallax.firebaseio.com/"
#define FIREBASE_AUTH "QRYIDUg5KAaqd3TqjDyLnv1UTcfiEddvukW5kF5F"
#define WIFI_SSID "Laxus"
#define WIFI_PASSWORD "qwerty123567"


void setup() {
  Serial.begin(9600);
  s.begin(9600);
  
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

void loop() {
  for (int i = 0; i < 1000; i++) {
    voltage = (voltage + (0.0049 * analogRead(A0)));
    delay(1);
  }

  voltage /= 1000;
  current = (voltage - 2.5)*2.508;

  //soc

  percentSOC = (voltage-3.73)*202.12766;
  //surface temp
  s.write("s");
  if (s.available()>0)
  {
    data=s.read();
  }

  float SOH = 0;
  SOH = (voltage/5)*100;

  Serial.print("\nVoltage sensed = ");
  Serial.print(voltage, 2);
  Serial.print("\nCurrent = ");
  Serial.print(current, 2);
  Serial.print("\n%SOC = ");
  Serial.print(percentSOC, 2);
  Serial.print("\n%Surface Temp = ");
  Serial.print(data);
  Serial.print("\n%SOH = ");
  Serial.print(SOH);

  Firebase.setFloat("voltage", voltage);
  // handle error
  if (Firebase.failed()) {
      Serial.print("\nsetting voltage failed:");
      Serial.println(Firebase.error());  
      return;
  }

  Firebase.setFloat("current", current);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting current failed:");
      Serial.println(Firebase.error());  
      return;
  }

  Firebase.setFloat("percentSOC", percentSOC);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting %SOC failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  Firebase.setFloat("Surface Temp", data);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting Temp failed:");
      Serial.println(Firebase.error());  
      return;
  }

 Firebase.setFloat("SOHe", SOH);
  // handle error
  if (Firebase.failed()) {
      Serial.print("\nsetting SOH failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  delay(1000);
}

//void setFirebase
