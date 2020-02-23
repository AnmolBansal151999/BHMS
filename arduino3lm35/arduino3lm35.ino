#include <SoftwareSerial.h>
SoftwareSerial s(5,6);// Rx,Tx
void setup() {
  Serial.begin(9600);
  s.begin(9600);

}

double Voltage = 0;
double Current = 0;
float T1 =0;
float T2 =0;
float T3 =0;
float Temp =0;
float Surf_temp = 0;

void loop() {
  
for(int i = 0; i < 1000; i++) {
  Voltage = (Voltage + (0.0049 * analogRead(A0))); // (5 V / 1024 (Analog) = 0.0049) which converter Measured analog input voltage to 5 V Range
  delay(1);
}

Voltage = Voltage /1000;
Current = (Voltage - 2.5)*2.508;

T1 = analogRead(A1);
T2 = analogRead(A2);
T3 = analogRead(A3);

Temp = (T1+T2+T3)/3;
Surf_temp = (Temp/1024.0)*500;

if(s.available()>0){
  s.write(Surf_temp);
}

Serial.print("\nSurface temperature in degree celcius: 0");
Serial.print(Surf_temp);
Serial.print("*C |");

Serial.print("\n Voltage Sensed (V) = "); // shows the measured voltage
Serial.print(Voltage,5); // the '2' after voltage allows you to display 2 digits after decimal point
Serial.print("\t Current (A) = "); // shows the voltage measured
Serial.print(Current,5); // the '2' after voltage allows you to display 2 digits after decimal point
}
