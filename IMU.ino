#include <Arduino.h>
#include <Dezibot.h>

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

Dezibot dezibot = Dezibot();

bool testPassed = true;

void init() {
    dezibot.begin();
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
    digitalWrite(18, LOW);
    pinMode(21, INPUT);
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

void readIMU(uint16_t sollX, uint16_t sollY, uint16_t sollZ, String type) {
  Serial.println("max-min values for 10 scans:");
  int32_t minx, maxx, miny, maxy, minz, maxz;
  for (uint i = 0; i < 10; i++) {
    IMUResult res = dezibot.motion.detection.getAcceleration();
    if (i == 0) {
      minx = res.x;
      maxx = res.x;
      miny = res.y;
      maxy = res.y;
      minz = res.z;
      maxz = res.z;
    } else {
      if (res.x < minx) {
        minx = res.x;
      }
      if (res.x > maxx) {
        maxx = res.x;
      }
      if (res.y < miny) {
        miny = res.y;
      }
      if (res.y > maxy) {
        maxy = res.y;
      }
      if (res.z < minz) {
        minz = res.z;
      }
      if (res.z > maxz) {
        maxz = res.z;
      }
    }
    delay(100);
  }
  Serial.print("MaxDiffX: ");
  Serial.println(
      compareTestValue(maxx-minx, sollX, type)? "true" : "false"
  );
  Serial.print("MaxDiffY: ");
  Serial.println(
      compareTestValue(maxy-miny, sollY, type)? "true" : "false"
  );
  Serial.print("MaxDiffZ: ");
  Serial.println(
      compareTestValue(maxz-minz, sollZ, type)? "true" : "false"
  );
}

void testIMU() {
  Serial.println("--- TEST IMU ---");
  readIMU(25, 25, 25, "max");
}

void testMotorR() {
    Serial.println("--- TEST MOTOR RIGHT ---");
    dezibot.motion.rotateAntiClockwise();
    readIMU(200,50,200, "min");
    dezibot.motion.stop();
}

void testMotorL() {
    Serial.println("--- TEST MOTOR LEFT ---");
    dezibot.motion.rotateClockwise();
    readIMU(200,50,200, "min");
    dezibot.motion.stop();
}

void runTests() {
    testPassed = true;
    testIMU();
    delay(2000);
    testMotorR();
    delay(2000);
    testMotorL();
}

void setup() {
    Serial.begin(115200);
    init();
    delay(10000);

    uint8_t attempts = 0;
    do {
        attempts++;
        Serial.print("Attempt: ");
        Serial.println(attempts);
        runTests();
        delay(10000);
    } while (!testPassed && attempts < 3);

    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}