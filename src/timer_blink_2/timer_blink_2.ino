

byte blinkOnOff = 0;

void setup() 
{
  blinkOnOff = 1;                // Enable the blinking.
  enableLED();                   // Set up the LED pin.
  enableCompareAInterrupt(128);  // Enable the timer interrupt at count of 128.

  Serial.begin(9600);
}

void loop() 
{
  static int count = 0;
  
 // Nothing to see here.  Move along.
 //PORTB |= (1<<5);
 //delay(500);
 //PORTB &= ~(1<<5);
 //delay(500);
 delay(1000);
 Serial.println(count++);
 

}

void enableLED()
{
  DDRB |= (1 << 5);   // Set PB5 as an output
}



void enableCompareAInterrupt(byte when)
{
  OCR0A = when;  // Output Compare Register 0 A set for when to interrupt.
  TIMSK0 |= 2;   // Enable the interrupt.
}


ISR(TIMER0_COMPA_vect)
{
  static byte on = 0;
  static int skip = 250;

  skip--;
  if(skip != 0)
  {
    return;
  }
  skip = 250;
  
  if(blinkOnOff == 0)
  {
    PORTB &= ~(1<<5);
    on = 0;
  }
  else
  {
    if(on == 0)
    {
      // if LED is off, turn it on
      PORTB |= (1<<5);
      on = 1;
      
    }
    else
    {
      // If LED is on, turn it off
      PORTB &= ~(1<<5);
      on = 0;
    }
  }
}
