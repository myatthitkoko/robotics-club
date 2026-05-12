#include <IRremote.h>

int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long timeStamp = 0;
unsigned long timeElapsed = 0;
unsigned long value = 0;
unsigned long cmd = 0;

// motor right | A
#define CW_A 13
#define CCW_A 12
#define ENABLE_A 11

// motor left | B
#define CW_B 7
#define CCW_B 8
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

void initializeLED() {
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  initializeMotorA();
  initializeMotorB();
  initializeLED();
}

void stopMotors() {
  analogWrite(ENABLE_A, 0);
  analogWrite(ENABLE_B, 0);
}

void turnClockwise(int motor) {
  switch (motor) {
    case 1:
      digitalWrite(CW_A, HIGH);
      digitalWrite(CCW_A, LOW);
      break;

    case 2:
      digitalWrite(CW_B, HIGH);
      digitalWrite(CCW_B, LOW);
      break;
  }
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

    value = results.value;

    if (value != 0xFFFFFFFF) {
      cmd = value;
    }

    timeStamp = millis();
    Serial.print("time last updated: ");
    Serial.println(millis());

    irrecv.resume();
  }

  timeElapsed = millis() - timeStamp;
  if (timeElapsed < 200) {

    if (cmd == 0xFF906F) {

      Serial.println(" -> ______________________________ ->");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println(" ->                                ->");

      turnCounterClockwise(1);
      turnCounterClockwise(2);
      updateMotor(1, 255);
      updateMotor(2, 255);
      digitalWrite(4, HIGH);
    }
      
    else if (cmd == 0xFFE01F) {

      Serial.println(" <- ______________________________ <-");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println(" <-                                <-");

      turnClockwise(2);
      turnClockwise(1);
      updateMotor(1, 255);
      updateMotor(2, 255);
      digitalWrite(2, HIGH);
    }
    
    else if (cmd == 0xFF30CF) {

      Serial.println(" -> ______________________________ none");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println(" ->                                none");

      turnCounterClockwise(1);
      updateMotor(1, 255);

    }

    else if (cmd == 0xFF18E7) {

      Serial.println("none______________________________ ->");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println("none                                ->");

      turnCounterClockwise(2);
      updateMotor(2, 255);
      digitalWrite(4, HIGH);
    }

  } else {

    stopMotors();
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
  }
}
