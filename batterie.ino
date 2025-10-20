#include <Arduino.h>
#include <Dezibot.h>

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

Dezibot dezibot = Dezibot();

bool testPassed = true;

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
// True High, False Low
bool getBatChgStat() {
  if (digitalRead(BAT_CHG_STAT) == HIGH) {
    return true;
  } else {
    return false;
  }
}

float readBatteryVoltage() {
  digitalWrite(BAT_ADC_EN, HIGH);
  delay(10);
  int adcValue = analogRead(BAT_ADC);
  digitalWrite(BAT_ADC_EN, LOW);
  float voltage = (adcValue / 4095.0) * 2 * 3.3;  // Assuming a 12-bit ADC and a voltage divider
  return voltage;
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
    delay(10000);

    Serial.print("Battery Charge Status: ");
    Serial.println(
        compareTestValue(getBatChgStat() ? 1 : 0, 0, "equal") ? "true" : "false"
    );

    float batteryVoltage = readBatteryVoltage();
    Serial.print("Battery Voltage: ");
    Serial.println(batteryVoltage);

    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}