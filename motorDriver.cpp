#include <IRremote.h>

int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;

unsigned long timeStamp = 0;
unsigned long timeElapsed = 0;
unsigned long value = 0;
unsigned long cmd = 0;

// motor front right | A
#define CW_A 2
#define CCW_A 3

// motor front left | B
#define CW_B 8
#define CCW_B 9

// motor back right | C
#define CW_C 4
#define CCW_C 5

// motor back left | D
#define CW_D 6
#define CCW_D 7

void initializeMotorA() {
  pinMode(CW_A, OUTPUT);
  pinMode(CCW_A, OUTPUT);
}

void initializeMotorB() {
  pinMode(CW_B, OUTPUT);
  pinMode(CCW_B, OUTPUT);
}

void initializeMotorC() {
  pinMode(CW_C, OUTPUT);
  pinMode(CCW_C, OUTPUT);
}

void initializeMotorD() {
  pinMode(CW_D, OUTPUT);
  pinMode(CCW_D, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  initializeMotorA();
  initializeMotorB();
  initializeMotorC();
  initializeMotorD();
}

void stopMotors() {
  digitalWrite(CW_A, LOW);
  digitalWrite(CCW_A, LOW);
  digitalWrite(CW_B, LOW);
  digitalWrite(CCW_B, LOW);
  digitalWrite(CW_C, LOW);
  digitalWrite(CCW_C, LOW);
  digitalWrite(CW_D, LOW);
  digitalWrite(CCW_D, LOW);
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

    case 3:
      digitalWrite(CW_C, HIGH);
      digitalWrite(CCW_C, LOW);
      break;

    case 4:
      digitalWrite(CW_D, HIGH);
      digitalWrite(CCW_D, LOW);
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
    
    case 3:
      digitalWrite(CW_C, LOW);
      digitalWrite(CCW_C, HIGH);
      break;

    case 4:
      digitalWrite(CW_D, LOW);
      digitalWrite(CCW_D, HIGH);
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
      turnCounterClockwise(3);
      turnCounterClockwise(4);
    }

    else if (cmd == 0xFFE01F) {

      Serial.println(" <- ______________________________ <-");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println(" <-                                <-");

      turnClockwise(1);
      turnClockwise(2);
      turnClockwise(3);
      turnClockwise(4);
    }
    
    else if (cmd == 0xFF30CF) { //turn right

      Serial.println(" -> ______________________________ ->");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println(" none                                none");

      stopMotors();
      turnCounterClockwise(1);
      turnCounterCLockwise(3);
    }

    else if (cmd == 0xFF18E7) { //turn left

      Serial.println("none______________________________ none");
      Serial.println("   |                              |");
      Serial.println("   |______________________________|");
      Serial.println("->                                ->");

      stopMotors();
      turnCounterClockwise(2);
      turnCounterCLockwise(4);
    }

  } else {

    stopMotors();
  }
}
