#include <Arduino.h>
#include <Dezibot.h>

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

Dezibot dezibot = Dezibot();
bool testPassed = true;

uint16_t getAverage(color color) {
  uint32_t sum = 0;
  for (uint i = 0; i < 10; i++) {
    sum = (uint32_t)sum + dezibot.colorDetection.getColorValue(color);
    delay(100);
    }
  return (uint16_t)((sum + 5) / 10);
}

bool compareTestValue(uint16_t mess, uint16_t soll, String type) {
    // messwert kleiner gleich soll
    if (type == "max") {
        Serial.print(mess);
        Serial.print(" <= ");
        Serial.print(soll);
        Serial.print("? --> ");
        if(mess > soll) {
            testPassed = false;
        }

        return mess <= soll;
    } else if (type == "min") {
        Serial.print(mess);
        Serial.print(" >= ");
        Serial.print(soll);
        Serial.print("? --> ");
        if(mess < soll) {
            testPassed = false;
        }
        return mess >= soll;
    } else if (type == "equal") {
        Serial.print(mess);
        Serial.print(" == ");
        Serial.print(soll);
        Serial.print("? --> ");
        if(mess != soll) {
            testPassed = false;
        }
        return mess == soll;
    } else {
        Serial.println("Fehler: Ungueltiger Vergleichstyp");
        return false;
    }
}

void testOff() {
    dezibot.multiColorLight.turnOffLed(BOTTOM);
    Serial.println("--- WHITE --- ");  // Turn off all LEDs
    delay(1000);
    Serial.print("RED: ");
    Serial.println(
        compareTestValue(getAverage(VEML_RED), 100, "max")? "true" : "false"
    );
    Serial.print("GREEN: ");
    Serial.println(
        compareTestValue(getAverage(VEML_GREEN), 100, "max")? "true" : "false"  
    );
    Serial.print("BLUE: ");
    Serial.println(
        compareTestValue(getAverage(VEML_BLUE), 100, "max")? "true" : "false"
    );
}

void testWhite() {
    dezibot.multiColorLight.setLed(BOTTOM, WHITE);
    Serial.println("--- WHITE --- "); 
    delay(1000);
    Serial.print("RED: ");
    Serial.println(
        compareTestValue(getAverage(VEML_RED), 150, "min")? "true" : "false"
    );
    Serial.print("GREEN: ");
    Serial.println(
        compareTestValue(getAverage(VEML_GREEN), 150, "min")? "true" : "false"
    );
    Serial.print("BLUE: ");
    Serial.println(
        compareTestValue(getAverage(VEML_BLUE), 150, "min")? "true" : "false"
    );
    dezibot.multiColorLight.turnOffLed(BOTTOM);
}

void testRed() {
    dezibot.multiColorLight.setLed(BOTTOM, RED); 
    Serial.println("--- RED --- ");
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.print("RED: ");
    Serial.println(
        compareTestValue(getAverage(VEML_RED), 150, "min")? "true" : "false"
    );
    Serial.print("GREEN: ");
    Serial.println(
        compareTestValue(getAverage(VEML_GREEN), 0, "min")? "true" : "false"
    );
    Serial.print("BLUE: ");
    Serial.println(
        compareTestValue(getAverage(VEML_BLUE), 0, "min")? "true" : "false"
    );
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

void testGreen() {
    dezibot.multiColorLight.setLed(BOTTOM, GREEN);
    Serial.println("--- GREEN --- ");
    delay(1000);
    // Serial.print("Red Sensor 10er average: ");
    Serial.print("RED: ");
    Serial.println(
        compareTestValue(getAverage(VEML_RED), 0, "min")? "true" : "false"
    );
    Serial.print("GREEN: ");
    Serial.println(
        compareTestValue(getAverage(VEML_GREEN), 200, "min")? "true" : "false"
    );
    Serial.print("BLUE: ");
    Serial.println(
        compareTestValue(getAverage(VEML_BLUE), 0, "min")? "true" : "false"
    );
    dezibot.multiColorLight.turnOffLed(BOTTOM);
};

void testBlue() {
    dezibot.multiColorLight.setLed(BOTTOM, BLUE);
    Serial.println("--- BLUE --- ");
    delay(1000);
    Serial.print("RED: ");
    Serial.println(
        compareTestValue(getAverage(VEML_RED), 150, "min")? "true" : "false"
    );
    Serial.print("GREEN: ");
    Serial.println(
        compareTestValue(getAverage(VEML_GREEN), 0, "min")? "true" : "false"
    );
    Serial.print("BLUE: ");
    Serial.println(
        compareTestValue(getAverage(VEML_BLUE), 0, "min")? "true" : "false"
    );
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
    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}