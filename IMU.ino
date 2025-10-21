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

void testIMU() {
  Serial.println("--- TEST IMU ---");
  readIMU(50, 50, 5000, "max");
}

void readIMU(uint16_t sollX, uint16_t sollY, uint16_t sollZ, String type) {
  Serial.println("average absolute acceleration over 10 samples:");
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
  Serial.print(", y: ");
  Serial.print((sumy + 5) / 10);
  Serial.print(", z: ");
  Serial.println((sumz + 5) / 10);

  Serial.print("ResultsX: ");
  Serial.println(
      compareTestValue((uint16_t)((sumx + 5) / 10), sollX, type)? "true" : "false"
  );
  Serial.print("ResultsY: ");
  Serial.println(
      compareTestValue((uint16_t)((sumy + 5) / 10), sollY, type)? "true" : "false"
  );
  Serial.print("ResultsZ: ");
  Serial.println(
      compareTestValue((uint16_t)((sumz + 5) / 10), sollZ, type)? "true" : "false"
  );
}

void testMotorR() {
    Serial.println("--- TEST MOTOR RIGHT ---");
    dezibot.motion.rotateAntiClockwise();
    readIMU(100,100,0, "min");
    dezibot.motion.stop();
}

void testMotorL() {
    Serial.println("--- TEST MOTOR LEFT ---");
    dezibot.motion.rotateClockwise();
    readIMU(100,100,0, "min");
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
    delay(10000);
    testIMU();
    delay(2000);
    testMotorR();
    delay(2000);
    testMotorL();
    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}