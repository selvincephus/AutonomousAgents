
#include<Servo.h>
#include<stdlib.h>

Servo servoLeft;
Servo servoRight;
int stayThreshold = 500; //it can be translated to 1000 milisecond maybe
int leftCount = 0;
int rightCount = 0;
float lightThreshold = 0.1;

void setup()
{
  // put your setup code here, to run once:
  pinMode(5, OUTPUT) ; pinMode(9, OUTPUT) ; pinMode(3, INPUT) ; pinMode(2, INPUT) ;
  servoLeft.attach(10);
  servoRight.attach(11);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  Serial. begin(9600) ;
  delay(100);
  lightThreshold = volts(A3) * 0.75;
}

void loop() {
  // put your main code here, to run repeatedly:
//    int irLeft = irDetect(9, 3, 38000) ; // Check for obj ect
    int irLeft = irReading(String("l"));
    Serial. print("Left");
    Serial. println(irLeft) ; // Display 1/0 no detect/detect
    
    // read the analog value for left phototransistor
    float leftPhoto = volts(A3);
    Serial.println(leftPhoto);
    // read the analog value for right phototransistor
    float rightPhoto = 0.24;
    if (leftPhoto < lightThreshold && rightPhoto > lightThreshold){
      foundMine(String("l"));
    }
    else if (leftPhoto > lightThreshold && rightPhoto < lightThreshold){
      foundMine(String("r"));
    }
    else if (leftPhoto < lightThreshold && rightPhoto < lightThreshold){
      // means both found mines
      foundMine(String("b"));
    }
//    int irRight = irDetect(5, 2, 38000) ; // Check for obj ect
    int irRight = irReading(String("r"));
    Serial. print("Right");
    Serial. println(irRight) ; // Display 1/0 no detect/detect
    delay(100) ;
    int counter = 0;
    if (irLeft == 1)
    {
      leftCount = 0;
    }
    else
    {
        leftCount++;
    }
    if (irRight == 1)
    {
      rightCount = 0;
    }
    else
    {
      rightCount++;
    }
//    if (irLeft == 0 && irRight == 1)
    if (leftCount >= 5 && rightCount < 5)
    {
      while (irLeft == 0 && counter < stayThreshold) {
        turnRight();
        irLeft = irReading(String("l"));
        counter = counter + 1;
        leftCount = 0;
        rightCount = 0;
//        Serial. println("Turning Right");
      }
    }
//    else if (irRight == 0 && irLeft == 1)
    else if (rightCount >= 5 && leftCount < 5)
    {
      while (irRight == 0 && counter < stayThreshold) {
        turnLeft();
        irRight = irReading(String("r"));
        counter = counter + 1;
        leftCount = 0;
        rightCount = 0;
      }
    }
//    else if (irLeft == 0 && irRight == 0)
    else if (leftCount >= 5 && rightCount >= 5)
    {
//      int rr = random();
//      if (rr < prob)
//      {
        while ((irLeft == 0 && irRight == 0) && counter < stayThreshold) {
          turn90degreesRight();
          irLeft = irReading(String("l"));
          irRight = irReading(String("r"));
          //delay(500);
          counter = counter + 1;
          leftCount = 0;
          rightCount = 0;
        }
//      }
//      else
//      {
//        while ((irLeft == 0 && irRight == 0) && counter < stayThreshold) {
//          turn90degreesLeft();
//          //delay(500);
//          counter = counter + 1;
//        }
//      }
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
  servoRight.writeMicroseconds(1700);
  servoLeft.writeMicroseconds(1700);
  }

void turnLeft()
  {
   servoRight.writeMicroseconds(1300);
   servoLeft.writeMicroseconds(1300);
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
  int freqSensivity = 46000;
  if (leftOrRight=="l")
  {
    irRead = irDetect(9, 3, freqSensivity) ;
//    Serial.println("LeftReading");
  }
  else
  {
    irRead = irDetect(5, 2, freqSensivity) ;
//    Serial.println("RightReading");
  }
  return irRead;
}

void stopMoving(){
  servoRight.writeMicroseconds(1500);
  servoLeft.writeMicroseconds(1500);
}

void foundMine(String leftOrRight){
  stopMoving();
  delay(3000);
  if (leftOrRight=="l")
  {
    turnRight();    
  }
  else if (leftOrRight=="r"){
    turnLeft(); 
  }
  else{
    // means both photo transistor find mines
    turn90degreesRight();
  }
  delay(300);
  goForward();
}

float volts(int adPin) // Measures volts at adPin
{ // Returns floating point voltage
  return float(analogRead(adPin)) * 5.0 / 1024.0;
}
