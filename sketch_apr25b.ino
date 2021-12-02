#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);
}
void loop() {
  topServo.write(115);
  delay(500);
  
  for(int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(6);
  }
  delay(500);
//  // Orange
//  bottomServo.write(50);
//  
  color = readColor();
  delay(50);  
  switch (color) {
    case 1:
    bottomServo.write(40);
    break;
    case 2:
    bottomServo.write(80);
    break;
    case 3:
    bottomServo.write(120);
    break;
    case 4:
    bottomServo.write(160);
    case 0:
    bottomServo.write(120);
//    break;
//    case 5:
//    bottomServo.write(150);
//    break;
//    case 6:
//    bottomServo.write(175);
//    break;
//    
    case 0:
    break;
  }
  delay(300);
  
  for(int i = 65; i > 20; i--) {
    topServo.write(i);
    delay(6);
  } 
  delay(200);
  
  for(int i = 20; i < 115; i++) {
    topServo.write(i);
    delay(6);
  }
  color=0;
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if(G>=160 & G<185 & B<=130){
    color = 1; // Blue
  }
  if(G>=150 & G<175 & B>135){
    color = 4; // Green
  }
  if(G>=180 & G<210){
    color = 2; // Red
  }
  if(G>=145 & G<160 & B<135){
    color = 3; // Yellow
  }
//  if(R<120 & R>110 & G>100 & G<110 & B<100 & B>95){
//    color = 4; // Green
//  }
//  if(R<56 & R>46 & G<=130 & G>120){
//    color = 5; // Brown
//  }
//  if (G<58 & G>45 & B<40 &B>26){
//    color = 6; // Blue
//  }
  Serial.print("Color: ");
  Serial.println(color);
  return color;  
}
