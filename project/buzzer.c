#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void play_song()
{
  float B = 617;
  float Ds = 777;
  float E = 824;
  float F = 873;
  float Fs = 925;
  float G = 980;
  float A2 = 1100;
  float B2 = 1234;

  float notes[30] = {B, 400000, E, 200000, G, 200000, F, 0, E, 0, B2, 0, A2, 0, Fs, 0, E, 0, G, 0, F, 0, Ds, 0, F, 0, B, 0};
  for (int i = 0; i < 30; i++) {
    buzzer_set_period(notes[i]);
    __delay_cycles(2500000);
  }
  buzzer_set_period(0);
}


    
    
  

