void setup() {
  // put your setup code here, to run once:
pinMode(5, OUTPUT) ; pinMode(9, OUTPUT) ; pinMode(A2, INPUT) ; pinMode(A4, INPUT) ;
Serial. begin(9600) ;
}

void loop() {
  // put your main code here, to run repeatedly:
    int irLeft = irDetect(9, A2, 38000) ; // Check for obj ect
    Serial. print("Left");
    Serial. println(irLeft) ; // Display 1/0 no detect/detect
    
    
    int irRight = irDetect(5, A4, 38000) ; // Check for obj ect
    Serial. print("Right");
    Serial. println(irRight) ; // Display 1/0 no detect/detect
    delay(100) ;
}// IR Obj ect Detection Function


int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
    tone(irLedPin, frequency, 8) ; // IRLED 38 kHz for at least 1 ms
    delay(1) ; // Wait 1 ms
    int ir = analogRead(irReceiverPin) ; // IR receiver -> ir variable
    delay(1) ; // Down time before recheck
    return ir; // Return 1 no detect, 0 detect
}
