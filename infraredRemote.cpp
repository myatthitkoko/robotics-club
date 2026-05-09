#include <IRremote.h>

int RECV_PIN = 3;

IRrecv irrecv(RECV_PIN);
decode_results results;

// motor right
#define CW_A 13
#define CCW_A 12
#define ENABLE_A 11

// motor left
#define CW_B 8
#define CCW_B 7
#define ENABLE_B 6

void initializeMotorA() {
  pinMode(ENABLE_A, OUTPUT);
  pinMode(CW_A, OUTPUT);
  pinMode(CCW_A, OUTPUT);
}

void initializeMotorB() {
  pinMode(ENABLE_B, OUTPUT);
  pinMode(CW_B, OUTPUT);
  pinMode(CCW_B, OUTPUT);
}

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();

  initializeMotorA();
  initializeMotorB();
}

void stopMotors() {
  analogWrite(ENABLE_A, 0);
  analogWrite(ENABLE_B, 0);
}

void turnCounterClockwise(int motor) {
  switch (motor) {
    case 1:
      digitalWrite(CW_A, LOW);
      digitalWrite(CCW_A, HIGH);
      break;

    case 2:
      digitalWrite(CW_B, LOW);
      digitalWrite(CCW_B, HIGH);
      break;
  }
}

void updateMotor(int motor, int motorSpeed) {
  switch (motor) {
    case 1:
      analogWrite(ENABLE_A, motorSpeed);
      break;

    case 2:
      analogWrite(ENABLE_B, motorSpeed);
      break;
  }
}

void loop() {

  if (irrecv.decode(&results)) {

    Serial.println(results.value, HEX);

    switch(results.value) {

      case 0xFF906F:
        Serial.println("Motor 1");
        turnCounterClockwise(1);
        updateMotor(1, 255);
        break;

      case 0xFFE01F:
        Serial.println("Motor 2");
        turnCounterClockwise(2);
        updateMotor(2, 255);
        break;

      default:
        stopMotors();
        break;
    }

    irrecv.resume();
  }
}
