
#include<Servo.h>
#include<stdlib.h>

Servo servoLeft;
Servo servoRight;
Servo servoSweep;
int stayThreshold = 500; //it can be translated to 1000 milisecond maybe
int irLeftOverTime = 0,irRightOverTime = 0;
int turnT = 30;
int maxOverTime = 50;
int minAngle = 35;
int maxAngle = 145;
int sweepStep = 5;
int sweepPos,sweepDir;

void setup()
{
  // put your setup code here, to run once:
  pinMode(5, OUTPUT) ; pinMode(9, OUTPUT) ; pinMode(3, INPUT) ; pinMode(2, INPUT) ;
  servoLeft.attach(10);
  servoRight.attach(11);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  servoSweep.attach(8);
  servoSweep.write(90);
  sweepPos = 90;
  sweepDir = 1;
  Serial. begin(9600);
  randomSeed(analogRead(0));
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
//    int irLeft = irDetect(9, 3, 38000) ; // Check for obj ect
    int irLeft = irReading(String("l"));
//    Serial. print("Left");
//    Serial. println(irLeft) ; // Display 1/0 no detect/detect
    
//    int irRight = irDetect(5, 2, 38000) ; // Check for obj ect
    int irRight = irReading(String("r"));
//    Serial.println("New reading");
//    Serial.println(irRight);
//    Serial. println(irRightOverTime) ; // Display 1/0 no detect/detect

    int counter = 0;
    
    
    
    if (irRight == 0) {
      irRightOverTime = min(irRightOverTime + 1, maxOverTime);
    } else {
      irRightOverTime = max(irRightOverTime -1, 0);
    }
    if (irLeft == 0) {
      irLeftOverTime = min(irLeftOverTime + 1, maxOverTime);
    } else {
      irLeftOverTime = max(irLeftOverTime - 1, 0);
    }
 
 
    
   if(irRightOverTime > turnT && irRightOverTime + 1.0/random(1000) > irLeftOverTime) {
      turnRight();
      irRightOverTime = max(irRightOverTime + random(-4,5),turnT+1);
      irLeftOverTime = 0;
   } else if (irLeftOverTime > turnT) {
      turnLeft();
      irLeftOverTime = max(irLeftOverTime + random(-4,5),turnT+1);
      irRightOverTime = 0;
   } else {
     goForward();
   }
   
   sweepPos += sweepStep * sweepDir;
   servoSweep.write(sweepPos);
   
   Serial. println(sweepPos) ;
   if (sweepPos >= maxAngle || sweepPos <= minAngle){
     sweepDir *= -1;
   }



   
   
}
    










void goForward()
  {
    servoRight.writeMicroseconds(1700-random(100));
    servoLeft.writeMicroseconds(1300+random(100));
  }

void turnRight()
  {
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1300);
  }

void turnLeft()
  {
   servoRight.writeMicroseconds(1700);
   servoLeft.writeMicroseconds(1700);
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
    delay(10) ; // Down time before recheck
    return ir; // Return 1 no detect, 0 detect
}

int irReading(String leftOrRight){
  int irRead = 0;
  if (leftOrRight=="l")
  {
    irRead = irDetect(9, 3, 38000) ;
//    Serial.println("LeftReading");
  }
  else
  {
    irRead = irDetect(5, 2, 38000) ;
//    Serial.println("RightReading");
  }
  return irRead;
}
