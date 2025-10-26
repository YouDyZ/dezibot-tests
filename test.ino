#include "Dezibot.h"

Dezibot dezibot;

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

void runTests() {
  Serial.println("IMU Tests:");

  Serial.print("X: ");
  for (int i = 0; i < 10; i++) {
    IMUResult res = dezibot.motion.detection.getAcceleration();
    Serial.print(res.x);
    Serial.print(' ');
    delay(10);
  }
  Serial.println();

  Serial.print("Y: ");
  for (int i = 0; i < 10; i++) {
    IMUResult res = dezibot.motion.detection.getAcceleration();
    Serial.print(res.y);
    Serial.print(' ');
    delay(10);
  }
  Serial.println();

  Serial.print("Z: ");
  for (int i = 0; i < 10; i++) {
    IMUResult res = dezibot.motion.detection.getAcceleration();
    Serial.print(res.z);
    Serial.print(' ');
    delay(10);
  }
  Serial.println();
}

void runTestsRGB() {
    Serial.print("RED Sensor: ");
    for (int i = 0; i < 10; i++) {
        Serial.print(dezibot.colorDetection.getColorValue(VEML_RED));
        Serial.print(" ");
        delay(10);
    }
    Serial.println();
    Serial.print("GREEN Sensor: ");
    for (int i = 0; i < 10; i++) {
        Serial.print(dezibot.colorDetection.getColorValue(VEML_GREEN));
        Serial.print(" ");
        delay(10);
    }
    Serial.println();
    Serial.print("BLUE Sensor: ");
    for (int i = 0; i < 10; i++) {  
        Serial.print(dezibot.colorDetection.getColorValue(VEML_BLUE));
        Serial.print(" ");
        delay(10);
    }
    Serial.println();
    Serial.print("WHITE Sensor: ");
    for (int i = 0; i < 10; i++) {
        Serial.print(dezibot.colorDetection.getColorValue(VEML_WHITE));
        Serial.print(" ");
        delay(10);
    }
    Serial.println();
}

void testIRSensor() {
  Serial.println("IR Sensor Front:");
  for (int i = 0; i < 10; i++) {

    Serial.print(dezibot.lightDetection.getValue(IR_FRONT));
    Serial.print(" ");
    delay(500);
  }
  Serial.println();
  Serial.println("IR Sensor Left:");
  for (int i = 0; i < 10; i++) {
    Serial.print(dezibot.lightDetection.getValue(IR_LEFT));
    Serial.print(" ");
    delay(500);
  }
  Serial.println();
  Serial.println("IR Sensor Back:");
  for (int i = 0; i < 10; i++) {
    Serial.print(dezibot.lightDetection.getValue(IR_BACK));
    Serial.print(" ");
    delay(500);
  }
  Serial.println();
  Serial.println("IR Sensor Right:");
  for (int i = 0; i < 10; i++) {
    Serial.print(dezibot.lightDetection.getValue(IR_RIGHT));
    Serial.print(" ");
  }
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

Serial.println("RGB LED und VEML TEST");
  dezibot.multiColorLight.turnOffLed(ALL);
  delay(1000);
  Serial.println("--- OFF --- ");
  for (int i = 0; i < 3; i++) {
    runTestsRGB();
    delay(5000);
  }
  dezibot.multiColorLight.turnOffLed(ALL);
  Serial.println("--- WHITE --- ");
  delay(1000);
  dezibot.multiColorLight.setLed(BOTTOM, dezibot.multiColorLight.color(100,100,100));
  delay(1000);
  for (int i = 0; i < 3; i++) {
    runTestsRGB();
    delay(5000);
  }
  dezibot.multiColorLight.turnOffLed(ALL);
  delay(500);
  dezibot.multiColorLight.setLed(BOTTOM, dezibot.multiColorLight.color(100,0,0));
  delay(1000);
  Serial.println("--- RED --- ");
  for (int i = 0; i < 3; i++) {
    runTestsRGB();
    delay(5000);
  }
  dezibot.multiColorLight.turnOffLed(ALL);
  delay(500);
  dezibot.multiColorLight.setLed(BOTTOM, dezibot.multiColorLight.color(0,100,0));
  delay(1000);
  Serial.println("--- GREEN --- ");
  for (int i = 0; i < 3; i++) {
    runTestsRGB();
    delay(5000);
  }

  dezibot.multiColorLight.turnOffLed(ALL);
  delay(500);
  dezibot.multiColorLight.setLed(BOTTOM, dezibot.multiColorLight.color(0,0,100));
  delay(1000);
  Serial.println("--- BLUE --- ");
  for (int i = 0; i < 3; i++) {
    runTestsRGB();
    delay(5000);
  }
  dezibot.multiColorLight.turnOffLed(ALL);
  Serial.println("RGB LED und VEML TEST Finished");

  delay(10000);
  for (int i = 0; i < 3; i++) {
    runTests();
    delay(5000);
  }
  Serial.println("IMU Test Finished");
  Serial.println("Starting Motor Tests in Left");
  dezibot.motion.rotateClockwise();
  delay(10000);
  for (int i = 0; i < 3; i++) {
    runTests();
    delay(5000);
  }
  dezibot.motion.stop();
  Serial.println("Motor Test 1 Finished");
  Serial.println("Starting Motor Tests Right");
  dezibot.motion.rotateAntiClockwise();
  delay(10000);
  for (int i = 0; i < 3; i++) {
    runTests();
    delay(5000);
  }
  dezibot.motion.stop();
  Serial.println("Motor Test 2 Finished");

  
  Serial.println("Infrared Sensor Test");
  Serial.println("IR Sensor Values. Sensors Off:");
  
  for (int i = 0; i < 3; i++) {
    Serial.print("IR Sensor Value: ");
    testIRSensor();
    delay(500);
  }
  Serial.println("IR Sensor Values Test 2:");
  digitalWrite(16, HIGH);
  for (int i = 0; i < 3; i++) {
    Serial.print("IR Sensor Value: ");
    testIRSensor();
    delay(500);
  }
  digitalWrite(16, LOW);
  delay(1000);
  digitalWrite(17, HIGH);
  for (int i = 0; i < 3; i++) {
    Serial.print("IR Sensor Value: ");
    testIRSensor();
    delay(500);
  }
  digitalWrite(17, LOW);
  delay(1000);
  digitalWrite(18, HIGH);
  for (int i = 0; i < 3; i++) {
    Serial.print("IR Sensor Value: ");
    testIRSensor();
    delay(500);
  }
  digitalWrite(18, LOW);
  Serial.println("Infrared Sensor Test Finished");
}

void loop() {
  // put your main code here, to run repeatedly:
}
