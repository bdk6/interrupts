//////////////////////////////////////////////////////////////////////////
/// timer_blink_1
/// Demonstration to show use of timer interrupt
/// See http://wrcooke.net/programming/arduino_interrupts.html
/// copyright Will Cooke 2022
/////////////////////////////////////////////////////////////////////////

#define SKIPVALUE         2000   // Sets the LED blink rate

void setup() 
{
  enableLED();                   // Set up the LED pin.
  enableCompareAInterrupt(128);  // Enable the timer interrupt at count of 128.

  Serial.begin(9600);            // Just to show normal program is still running.
}

void loop() 
{
  static int count = 0;

  delay(1000);                  // We can still use delay.  It is unaffected.
  Serial.println(count++);      // Show the world our normal program still running.
}

// Need to set the LED pin as an output.  
void enableLED()
{
  DDRB |= (1 << 5);   // Set PB5 as an output
}


// Need to enable the Timer 0 Output Compare Register A interrupts and set the 
// match value to interrupt on.
void enableCompareAInterrupt(byte when)
{
  OCR0A = when;  // Output Compare Register 0 A set for when to interrupt.
  TIMSK0 |= 2;   // Enable the interrupt.
}

//  This is the Interrupt Service Routine (ISR) for Timer 0 Comparator A
//  It will run every time the counter value matches our set value (when parameter 
//  in enableComparatorAInterrupt function.)  It will interrupt about 1000 times 
//  per second, the same as the millis() interrupt.
ISR(TIMER0_COMPA_vect)
{
  static byte on = 0;
  static int skip = SKIPVALUE;

  skip--;            // skip tells us to skip interrupts to slow down blink rate
  if(skip != 0)      // We decrement it and only run the rest of the ISR if it is 
  {                  // is zero.
    return;
  }
  skip = SKIPVALUE;       // When it is zero, we reset it and run the rest.
  
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
