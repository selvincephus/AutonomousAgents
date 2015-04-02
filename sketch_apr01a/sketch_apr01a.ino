
#include<Servo.h>
#include<stdlib.h>

Servo servoLeft;
Servo servoRight;
int prob = 1;


void setup()
{
  // put your setup code here, to run once:
  pinMode(5, OUTPUT) ; pinMode(9, OUTPUT) ; pinMode(3, INPUT) ; pinMode(2, INPUT) ;
  servoLeft.attach(10);
  servoRight.attach(11);
  //servoLeft.writeMicroseconds(1500);
  //servoRight.writeMicroseconds(1500);
  Serial. begin(9600) ;
}

void loop() {
  // put your main code here, to run repeatedly:
    int irLeft = irDetect(9, 3, 38000) ; // Check for obj ect
    Serial. print("Left");
    Serial. println(irLeft) ; // Display 1/0 no detect/detect
    
    int irRight = irDetect(5, 2, 38000) ; // Check for obj ect
    Serial. print("Right");
    Serial. println(irRight) ; // Display 1/0 no detect/detect
    delay(100) ;
    
    if (irLeft == 0 && irRight == 1)
      //While loop
      turnRight();
    else if (irRight == 0 && irLeft == 1)
          turnLeft();
    else if (irLeft == 0 && irRight == 0)
        {
        int rr = random();
        if (rr < prob)
          {
          turn90degreesRight();
          //delay(500);
          }
        else
        {
          turn90degreesLeft();
          //delay(500);
        }
        }
    else
       goForward();
}// IR Obj ect Detection Function

void goForward()
      {
      servoRight.writeMicroseconds(1700);
      servoLeft.writeMicroseconds(1300);
      }

void turnRight()
  {
  servoRight.writeMicroseconds(1580);
  servoLeft.writeMicroseconds(1700);
  }

void turnLeft()
  {
   servoRight.writeMicroseconds(1700);
   servoLeft.writeMicroseconds(1580);
  }
  
void turn90degreesRight()
  {
   servoRight.writeMicroseconds(1500);
   servoLeft.writeMicroseconds(1300);
  }
void turn90degreesLeft()
  {
   servoRight.writeMicroseconds(1700);
   servoLeft.writeMicroseconds(1500);
  }
  
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
    tone(irLedPin, frequency, 8) ; // IRLED 38 kHz for at least 1 ms
    delay(1) ; // Wait 1 ms
    int ir = digitalRead(irReceiverPin) ; // IR receiver -> ir variable
    delay(1) ; // Down time before recheck
    return ir; // Return 1 no detect, 0 detect
}
