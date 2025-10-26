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



void readIMU(uint16_t sollX, uint16_t sollY, uint16_t sollZ, String type) {
  Serial.println("min and max values for 10 scans:");
  int32_t minx = 0;
  int32_t maxx = 0;
  int32_t miny = 0;
  int32_t maxy = 0;
  int32_t minz = 0;
  int32_t maxz = 0;
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
      compareTestValue(maxx-minx, sollX, type)? "true" : "false"
  );
  Serial.print("ResultsY: ");
  Serial.println(
      compareTestValue(maxy-miny, sollY, type)? "true" : "false"
  );
  Serial.print("ResultsZ: ");
  Serial.println(
      compareTestValue(maxz-minz, sollZ, type)? "true" : "false"
  );
}

void testIMU() {
  Serial.println("--- TEST IMU ---");
  readIMU(100, 50, -1, "max");
}

void testMotorR() {
    Serial.println("--- TEST MOTOR RIGHT ---");
    dezibot.motion.rotateAntiClockwise();
    readIMU(200,0,0, "min");
    dezibot.motion.stop();
}

void testMotorL() {
    Serial.println("--- TEST MOTOR LEFT ---");
    dezibot.motion.rotateClockwise();
    readIMU(200,0,0, "min");
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

    // Run Tests up to 3 Times, it need to pas once
    uint8_t attempts = 0;
    do {
        attempts++;
        Serial.print("Attempt: ");
        Serial.println(attempts);
        runTests();
    } while (!testPassed && attempts < 3);

    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}

arduino-cli compile --fqbn esp32:esp32:esp32s3usbotg:USBMode=hwcdc,PartitionScheme=default,DebugLevel=none,EraseFlash=none test/test.ino && arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3usbotg:USBMode=hwcdc,PartitionScheme=default,DebugLevel=none,EraseFlash=none test/test.ino && arduino-cli monitor -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3usbotg --config 115200