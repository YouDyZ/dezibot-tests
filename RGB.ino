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

void testOff() {
    dezibot.multiColorLight.turnOffLed(BOTTOM);
    Serial.println("--- WHITE --- ");  // Turn off all LEDs
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.println("RED: ");
    Serial.println(getAverage(VEML_RED));
    Serial.println("GREEN: ");
    Serial.println(getAverage(VEML_GREEN));
    Serial.println("BLUE: ");
    Serial.println(getAverage(VEML_BLUE));
}

void testWhite() {
    dezibot.multiColorLight.setLed(BOTTOM, WHITE);
    Serial.println("--- WHITE --- ");  // Turn off all LEDs
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.println("RED: ");
    Serial.println(getAverage(VEML_RED));
    Serial.println("GREEN: ");
    Serial.println(getAverage(VEML_GREEN));
    Serial.println("BLUE: ");
    Serial.println(getAverage(VEML_BLUE));
    dezibot.multiColorLight.turnOffLed(BOTTOM);
}

void testRed() {
    dezibot.multiColorLight.setLed(BOTTOM, RED);  // Turn off all LEDs
    Serial.println("--- RED --- ");
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.println("RED: ");
    Serial.println(getAverage(VEML_RED));
    Serial.println("GREEN: ");
    Serial.println(getAverage(VEML_GREEN));
    Serial.println("BLUE: ");
    Serial.println(getAverage(VEML_BLUE));
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

void testGreen() {
    dezibot.multiColorLight.setLed(BOTTOM, GREEN);
    Serial.println("--- GREEN --- ");
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.println("RED: ");
    Serial.println(getAverage(VEML_RED));
    Serial.println("GREEN: ");
    Serial.println(getAverage(VEML_GREEN));
    Serial.println("BLUE: ");
    Serial.println(getAverage(VEML_BLUE));
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

void testBlue() {
    dezibot.multiColorLight.setLed(BOTTOM, BLUE);  // Turn off all LEDs
    Serial.println("--- BLUE --- ");
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.println("RED: ");
    Serial.println(getAverage(VEML_RED));
    Serial.println("GREEN: ");
    Serial.println(getAverage(VEML_GREEN));
    Serial.println("BLUE: ");
    Serial.println(getAverage(VEML_BLUE));
    dezibot.multiColorLight.turnOffLed(BOTTOM);
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
    delay(1000);
    testOff();
    delay(2000);
    testWhite();
    delay(2000);
    testRed();
    delay(2000);
    testGreen();
    delay(2000);
    testBlue();
    delay(2000);
    Serial.end();
}

void loop() {
}