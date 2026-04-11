// C++ code
//

#define Pin1A 13
#define Pin2A 12
#define EN12 11
#define Pin3A 7
#define Pin4A 8
#define EN34 3

const int CW=1;
const int CCW=2;

void setup()
{
  pinMode(Pin1A, OUTPUT);
  pinMode(Pin2A, OUTPUT);
  pinMode(EN12, OUTPUT);
  
  pinMode(Pin3A, OUTPUT);
  pinMode(Pin4A, OUTPUT);
  pinMode(EN34, OUTPUT);
}

void motor(int motor, int pwm, int dir)
{
    int drive1Pin, drive2Pin, driveENPin;
    String motorTitle;

    if(motor==1)
    {
        drive1Pin = Pin1A;
        drive2Pin = Pin2A;
        driveENPin = EN12;
        motorTitle = "Motor 1";
    }
    else if (motor==2)
    {
        drive1Pin = Pin3A;
        drive2Pin = Pin4A;
        driveENPin = EN34;
        motorTitle = "Motor 2";
    }

    if (pwm == 0) {
        digitalWrite(drive1Pin, LOW);
        digitalWrite(drive2Pin, LOW);
        return;
    }

    if (dir == CCW) {
        digitalWrite(drive1Pin, HIGH);
        digitalWrite(drive2Pin, LOW);
    }
    else if (dir == CW) {
        digitalWrite(drive1Pin, LOW);
        digitalWrite(drive2Pin, HIGH);
    }

    analogWrite(driveENPin, pwm);
}

void linearMotion() {
  motor(1,255,CW);
  motor(2,255,CW);
  delay(10000);
}

void slowAndStop() {
  for (int i=0; i <=255; i+=10) {
  	motor(1,255-i,CW);
  	motor(2,255-i,CW);
    delay(200);
  }
  motor(1,0,CCW);
  motor(2,0,CCW);
}

void loop()
{ 
  
  linearMotion();
  slowAndStop();
  delay(10000);
  
  //turn right
  motor(1,255,CCW);
  motor(2,170,CCW);
  delay(10000);
  
  //constant speed in a straight line
  motor(1,255,CCW);
  motor(2,255,CCW);
  delay(10000);
  
  //turn left
  motor(1,170,CCW);
  motor(2,255,CCW);
  delay(10000);
  
}
