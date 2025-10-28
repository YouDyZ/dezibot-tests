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

// all off
void testIR1() {
    Serial.println("--- IR Transistor 1 ---");
    uint32_t frontIR = dezibot.lightDetection.getAverageValue(IR_FRONT, 10, 50);
    uint32_t leftIR = dezibot.lightDetection.getAverageValue(IR_LEFT, 10, 50);
    uint32_t backIR = dezibot.lightDetection.getAverageValue(IR_BACK, 10, 50);
    uint32_t rightIR = dezibot.lightDetection.getAverageValue(IR_RIGHT, 10, 50);
    uint32_t frontDL = dezibot.lightDetection.getAverageValue(DL_FRONT, 10, 50);
    uint32_t botDL = dezibot.lightDetection.getAverageValue(DL_BOTTOM, 10, 50);

    Serial.print("front: ");
    Serial.println(
        compareTestValue(frontIR, 100, "max")? "true" : "false");
    Serial.print("left: ");
    Serial.println(
        compareTestValue(leftIR, 100, "max")? "true" : "false");
    Serial.print("back: ");
    Serial.println(
        compareTestValue(backIR, 100, "max")? "true" : "false");
    Serial.print("right: ");
    Serial.println(
        compareTestValue(rightIR, 100, "max")? "true" : "false");
    
    Serial.print("front DL: ");
    Serial.println(
        compareTestValue(frontDL, 1000, "max")? "true" : "false");
    Serial.print("bottom DL: ");
    Serial.println(
        compareTestValue(botDL, 1000, "max")? "true" : "false");
}

// DL Front active
void testIR2() {
    Serial.println("--- IR Transistor 2 ---");
    digitalWrite(16, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getAverageValue(IR_FRONT, 10, 50);
    uint32_t leftIR = dezibot.lightDetection.getAverageValue(IR_LEFT, 10, 50);
    uint32_t backIR = dezibot.lightDetection.getAverageValue(IR_BACK, 10, 50);
    uint32_t rightIR = dezibot.lightDetection.getAverageValue(IR_RIGHT, 10, 50);
    uint32_t frontDL = dezibot.lightDetection.getAverageValue(DL_FRONT, 10, 50);
    uint32_t botDL = dezibot.lightDetection.getAverageValue(DL_BOTTOM, 10, 50);
    Serial.print("front: ");
    Serial.println(
        compareTestValue(frontIR, 3000, "max")? "true" : "false");
    Serial.print("left: ");
    Serial.println(
        compareTestValue(leftIR, 500, "max")? "true" : "false");
    Serial.print("back: ");
    Serial.println(
        compareTestValue(backIR, 500, "max")? "true" : "false");
    Serial.print("right: ");
    Serial.println(
        compareTestValue(rightIR, 500, "max")? "true" : "false");
    Serial.print("front DL: ");
    Serial.println(
        compareTestValue(frontDL, 3500, "min")? "true" : "false");
    Serial.print("bottom DL: ");
    Serial.println(
        compareTestValue(botDL, 1000, "max")? "true" : "false");
    digitalWrite(16, LOW);
    
    delay(100);
}

// front and right active
void testIR3() {
    Serial.println("--- IR Transistor 3 ---");
    digitalWrite(17, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getAverageValue(IR_FRONT, 10, 50);
    uint32_t leftIR = dezibot.lightDetection.getAverageValue(IR_LEFT, 10, 50);
    uint32_t backIR = dezibot.lightDetection.getAverageValue(IR_BACK, 10, 50);
    uint32_t rightIR = dezibot.lightDetection.getAverageValue(IR_RIGHT, 10, 50);
    uint32_t frontDL = dezibot.lightDetection.getAverageValue(DL_FRONT, 10, 50);
    uint32_t botDL = dezibot.lightDetection.getAverageValue(DL_BOTTOM, 10, 50);
    Serial.print("front: ");
    Serial.println(
        compareTestValue(frontIR, 2000, "min")? "true" : "false");
    Serial.print("left: ");
    Serial.println(
        compareTestValue(leftIR, 500, "max")? "true" : "false");
    Serial.print("back: ");
    Serial.println(
        compareTestValue(backIR, 500, "max")? "true" : "false");
    Serial.print("right: ");
    Serial.println(
        compareTestValue(rightIR, 2000, "min")? "true" : "false");
    Serial.print("front DL: ");
    Serial.println(
        compareTestValue(frontDL, 2500, "max")? "true" : "false");
    Serial.print("bottom DL: ");
    Serial.println(
        compareTestValue(botDL, 1000, "max")? "true" : "false");
    digitalWrite(17, LOW);
    delay(100);
}

// left and back active
void testIR4() {
    Serial.println("--- IR Transistor 4 ---");
    digitalWrite(18, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getAverageValue(IR_FRONT, 10, 50);
    uint32_t leftIR = dezibot.lightDetection.getAverageValue(IR_LEFT, 10, 50);
    uint32_t backIR = dezibot.lightDetection.getAverageValue(IR_BACK, 10, 50);
    uint32_t rightIR = dezibot.lightDetection.getAverageValue(IR_RIGHT, 10, 50);
    uint32_t frontDL = dezibot.lightDetection.getAverageValue(DL_FRONT, 10, 50);
    uint32_t botDL = dezibot.lightDetection.getAverageValue(DL_BOTTOM, 10, 50);
    Serial.print("front: ");
    Serial.println(
        compareTestValue(frontIR, 500, "max")? "true" : "false");
    Serial.print("left: ");
    Serial.println(
        compareTestValue(leftIR, 3000, "min")? "true" : "false");
    Serial.print("back: ");
    Serial.println(
        compareTestValue(backIR, 3000, "min")? "true" : "false");
    Serial.print("right: ");
    Serial.println(
        compareTestValue(rightIR, 500, "max")? "true" : "false");
    Serial.print("front DL: ");
    Serial.println(
        compareTestValue(frontDL, 1000, "max")? "true" : "false");
    Serial.print("bottom DL: ");
    Serial.println(
        compareTestValue(botDL, 1000, "max")? "true" : "false");
    digitalWrite(18, LOW);
    delay(100);
}

void testIRLed() {
    Serial.println("--- Test Bottom IR LED ---");
    Serial.print("off: ");
    Serial.println(
        compareTestValue(digitalRead(21), 0, "equal")? "true" : "false"
    );
    delay(100);
    Serial.print("Error Intended: ");
    dezibot.infraredLight.front.setState(true);
    Serial.print("front: ");
    delay(10);
    Serial.println(
        compareTestValue(digitalRead(21), 0, "equal")? "true" : "false"
    );
    delay(10);
    Serial.print("Error Intended: ");
    dezibot.infraredLight.front.setState(false);
    delay(100);
    Serial.print("Error Intended: ");
    dezibot.infraredLight.bottom.setState(true);
    Serial.print("bottom: ");
    delay(10);
    Serial.println(compareTestValue(
        digitalRead(21), 1, "equal")? "true" : "false"
    );
    delay(10);
    Serial.print("Error Intended: ");
    dezibot.infraredLight.bottom.setState(false);
}

void setup() {
    Serial.begin(115200);
    init();
    delay(10000);
    testIR1();
    delay(1000);
    testIR2();
    delay(1000);
    testIR3();
    delay(1000);
    testIR4();
    delay(1000);
    testIRLed();

    Serial.print("Test: ");
    Serial.println(testPassed ? "PASSED" : "FAILED");
}

void loop() {
}