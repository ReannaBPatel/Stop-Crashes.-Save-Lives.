#include <Arduino.h>
#include <zirconLib.h>
#include <cmath>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  InitializeZircon();
}

double firstcarV() {
  int addx = 0;
  int addy = 0;
  for (int i = 1; i<4; i++) {
  int angleOne = ((i - 1)*45)+60;
  if (angleOne>360) {
    angleOne = angleOne - 360;
  }
  double x = cos(angleOne * (180/3.14159))*readBall(i);
  double y = sin(angleOne * (180/3.14159))*readBall(i);
  addx = addx + x;
  addy = addy + y;
  }
  double CarOne = atan2(addy, addx);
  CarOne = CarOne*180/3.14159;
  delay(100);
  int addxV = 0;
  int addyV = 0;
  for (int i = 1; i<4; i++) {
  int angleOneV = ((i - 1)*45)+60;
  if (angleOneV>360) {
    angleOneV = angleOneV - 360;
  }
  double xV = cos(angleOneV * (180/3.14159))*readBall(i);
  double yV = sin(angleOneV * (180/3.14159))*readBall(i);
  addxV = addxV + xV;
  addyV = addyV + yV;
  }
  double CarOneV = atan2(addyV, addxV);
  CarOneV = CarOneV*180/3.14159;
  double rate1 = CarOneV - CarOne;
  return rate1;
}

double secondcarV() {
  int addx2 = 0;
  int addy2 = 0;
  for (int i = 5; i<8; i++) {
  int angle2 = ((i - 1)*45)+60;
  if (angle2>360) {
    angle2 = angle2 - 360;
  }
  //readBall(i) = magnitude
  double x2 = cos(angle2 * (180/3.14159))*readBall(i);
  double y2 = sin(angle2 * (180/3.14159))*readBall(i);
  addx2 = addx2 + x2;
  addy2 = addy2 + y2;
  }
  double CarTwo = atan2(addy2, addx2);
  CarTwo = CarTwo*180/3.14159;
  delay(100);
  int addxV2 = 0;
  int addyV2 = 0;
  for (int i = 5; i<8; i++) {
  int angleTwoV = ((i - 1)*45)+60;
  if (angleTwoV>360) {
    angleTwoV = angleTwoV - 360;
  }
  double xV2 = cos(angleTwoV * (180/3.14159))*readBall(i);
  double yV2 = sin(angleTwoV * (180/3.14159))*readBall(i);
  addxV2 = addxV2 + xV2;
  addyV2 = addyV2 + yV2;
  }
  double CarTwoV = atan2(addyV2, addxV2);
  CarTwoV = CarTwoV*180/3.14159;
  double rate2 = CarTwoV - CarTwo;
  return rate2;
}

double drt(int rate, int distance) {
  int time = distance/rate;
  return time;
}

double firstcarD() {
  int addxD = 0;
  int addyD = 0;
  for (int i = 1; i<4; i++) {
  int angleOneD = ((i - 1)*45)+60;
  if (angleOneD>360) {
    angleOneD = angleOneD - 360;
  }
  double xD = cos(angleOneD * (180/3.14159))*readBall(i);
  double yD = sin(angleOneD * (180/3.14159))*readBall(i);
  addxD = addxD + xD;
  addyD = addyD + yD;
  }
  double CarOneD = atan2(addyD, addxD);
  CarOneD = CarOneD*180/3.14159;
  double D = abs(CarOneD);
  return D;
}

double secondcarD() {
  int addxD2 = 0;
  int addyD2 = 0;
  for (int i = 5; i<8; i++) {
  int angleD2 = ((i - 1)*45)+60;
  if (angleD2>360) {
    angleD2 = angleD2 - 360;
  }
  //readBall(i) = magnitude
  double xD2 = cos(angleD2 * (180/3.14159))*readBall(i);
  double yD2 = sin(angleD2 * (180/3.14159))*readBall(i);
  addxD2 = addxD2 + xD2;
  addyD2 = addyD2 + yD2;
  }
  double CarTwoD = atan2(addyD2, addxD2);
  CarTwoD = CarTwoD*180/3.14159;
  double D2 = abs(CarTwoD);
  return D2;
}

void loop() { 
  // put your main code here, to run repeatedly:
  double car1V = 0;
  car1V = firstcarV();
  double car1D = 0;
  car1D = firstcarD();
  double time1 = 0;
  time1 = drt(car1V, car1D);
  double car2V = 0;
  car2V = secondcarV();
  double car2D = 0;
  car2D = secondcarD();
  double time2 = 0;
  time2 = drt(car2V, car2D);
  time1 = abs(time1);
  time2 = abs(time2);
  Serial.println(String(time1) + " compared to " + String(time2));
  int comparison = abs(time1 - time2);
  if (time1 < 3 && time1 > -3) {
    Serial.println("Safe. Keep going.");
  } else if (time2 < 3 && time2 > -3) {
    Serial.println("Safe. Keep going.");
  } else if (comparison <= 20) {
    Serial.println("Slow down. High risk for a car crash.");
  } else {
    Serial.println("Safe. Keep going.");
  }
delay(1000);
}

// put function definitions here: