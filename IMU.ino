#include <Arduino.h>
#include <Dezibot.h>

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

Dezibot dezibot = Dezibot();

uint16_t getAverage(color color) {
  uint32_t sum = 0;
    for (uint i = 0; i < 10; i++) {
      uint16_t scan =
        //Serial.print(scan);
        Serial.print(" ");
      sum = (uint32_t)sum + dezibot.colorDetection.getColorValue(color);
      ;
      Serial.print(sum);
      delay(100);
    }
    Serial.print(color);
    Serial.print(" Sensor 10er average: ");
    return (uint16_t)((sum + 5) / 10);
}

void testIMU() {
  Serial.println("--- TEST IMU ---");
  uint32_t sumx = 0;
  uint32_t sumy = 0;
  uint32_t sumz = 0;
  for (uint i = 0; i < 10; i++) {
    IMUResult res = dezibot.motion.detection.getAcceleration();
    //Serial.print(scan);
    sumx = sumx + abs((int32_t)res.x);
    sumy = sumy + abs((int32_t)res.y);
    sumz = sumz + abs((int32_t)res.z);
    delay(100);
  }
  //sumx = ((sumx+5)/10);
  //sumy = ((sumy+5)/10);
  //sumz = ((sumz+5)/10);
  Serial.print("x: ");
  Serial.print((sumx + 5) / 10);
  Serial.print("/");
  Serial.print(((sumx + 5) / 10) / 16);
  Serial.print("g, y: ");
  Serial.print((sumy + 5) / 10);
  Serial.print("/");
  Serial.print(((sumy + 5) / 10) / 16);
  Serial.print("g, z: ");
  Serial.print((sumz + 5) / 10);
  Serial.print("/");
  Serial.print(((sumz + 5) / 10) / 16);
  Serial.println("g");
}

void testMotorR() {
    Serial.println("--- TEST MOTOR RIGHT ---");
    dezibot.motion.rotateAntiClockwise();
    testIMU();
    dezibot.motion.stop();
}

void testMotorL() {
    Serial.println("--- TEST MOTOR LEFT ---");
    dezibot.motion.rotateClockwise();
    testIMU();
    dezibot.motion.stop();
}

void init() {
    dezibot.begin();
    //a. GPIO16, GPIO17, GPIO18 als Ausgang, Low geschaltet.
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    // b. GPIO21 als Eingang, ohne interne Pull-Up-/Down-Widerstände.
    pinMode(21, INPUT);
}

void setup() {
    Serial.begin(115200);
    init();
    delay(500);
    testIMU();
    testMotorR();
    testMotorL();
    Serial.end();
}

void loop() {
}