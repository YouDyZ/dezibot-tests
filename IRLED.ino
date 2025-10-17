#include <Arduino.h>
#include <Dezibot.h>

#define BAT_CHG_STAT 39
#define BAT_ADC 10
#define BAT_ADC_EN 9
#define VUSB_SENS 38
#define FL_PT_EN 37

Dezibot dezibot = Dezibot();

void testIR1() {
    uint32_t frontIR = dezibot.lightDetection.getValue(IR_FRONT);
    uint32_t leftIR = dezibot.lightDetection.getValue(IR_LEFT);
    uint32_t backIR = dezibot.lightDetection.getValue(IR_BACK);
    uint32_t rightIR = dezibot.lightDetection.getValue(IR_RIGHT);

    Serial.print("front: ");
    Serial.print(frontIR);
    Serial.print(", ");
    Serial.print("left: ");
    Serial.print(leftIR);
    Serial.print(", ");
    Serial.print("back: ");
    Serial.print(backIR);
    Serial.print(", ");
    Serial.print("right: ");
    Serial.println(rightIR);
}

void testIR2() {
    digitalWrite(16, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getValue(IR_FRONT);
    uint32_t leftIR = dezibot.lightDetection.getValue(IR_LEFT);
    uint32_t backIR = dezibot.lightDetection.getValue(IR_BACK);
    uint32_t rightIR = dezibot.lightDetection.getValue(IR_RIGHT);
    Serial.print("front: ");
    Serial.print(frontIR);
    Serial.print(", ");
    Serial.print("left: ");
    Serial.print(leftIR);
    Serial.print(", ");
    Serial.print("back: ");
    Serial.print(backIR);
    Serial.print(", ");
    Serial.print("right: ");
    Serial.println(rightIR);
    digitalWrite(16, LOW);
    delay(100);
}

void testIR3() {
    digitalWrite(17, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getValue(IR_FRONT);
    uint32_t leftIR = dezibot.lightDetection.getValue(IR_LEFT);
    uint32_t backIR = dezibot.lightDetection.getValue(IR_BACK);
    uint32_t rightIR = dezibot.lightDetection.getValue(IR_RIGHT);
    Serial.print("front: ");
    Serial.print(frontIR);
    Serial.print(", ");
    Serial.print("left: ");
    Serial.print(leftIR);
    Serial.print(", ");
    Serial.print("back: ");
    Serial.print(backIR);
    Serial.print(", ");
    Serial.print("right: ");
    Serial.println(rightIR);
    digitalWrite(17, LOW);
    delay(100);

}

void testIR4() {
    digitalWrite(18, HIGH);
    delay(100);
    uint32_t frontIR = dezibot.lightDetection.getValue(IR_FRONT);
    uint32_t leftIR = dezibot.lightDetection.getValue(IR_LEFT);
    uint32_t backIR = dezibot.lightDetection.getValue(IR_BACK);
    uint32_t rightIR = dezibot.lightDetection.getValue(IR_RIGHT);
    Serial.print("front: ");
    Serial.print(frontIR);
    Serial.print(", ");
    Serial.print("left: ");
    Serial.print(leftIR);
    Serial.print(", ");
    Serial.print("back: ");
    Serial.print(backIR);
    Serial.print(", ");
    Serial.print("right: ");
    Serial.println(rightIR);
    digitalWrite(18, LOW);
    delay(100);
}

void testIRLed() {
    Serial.println("--- Test IR LED ---");
    Serial.print("off: ");
    Serial.println(digitalRead(21));
    
    delay(100);
    Serial.print("front: ");
    dezibot.infraredLight.front.setState(true);
    delay(10);
    Serial.println(digitalRead(21));
    delay(10);
    dezibot.infraredLight.front.setState(false);
    delay(100);
    Serial.print("bottom: ");
    dezibot.infraredLight.bottom.setState(true);
    delay(10);
    Serial.println(digitalRead(21));
    delay(10);
    dezibot.infraredLight.bottom.setState(false);
}

void init() {
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
    testIRTransitor();
    testIRLed();
}

void loop() {
}