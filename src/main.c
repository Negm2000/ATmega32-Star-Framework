#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TMR/TMR0_interface.h"
 

 void ToggleLEDs(void){
    DIO_PinDigitalToggle(PORTD, PIN7 | PIN6 | PIN0 | PIN1);
 }

void doNothing(void){}

uint32 last = 0;

int main() {
  // put your setup code here, to run once:
  DIO_PinMode(PORTB,PIN3, OUTPUT);
  // ST_TMR0_Default_Config.waveform_generation_mode = CTC;
  // ST_TMR0_Default_Config.compare_match_output_mode = OC_TOGGLE;
  // ST_TMR0_Default_Config.prescaler_select = PRESCALER_64;
  TMR0_Config(&ST_TMR0_Default_Config);
  // TMR0_SetOverflowPeriod_ms(1000);
  // TMR0_SetOverflowCallback(ToggleLEDs);
  // TMR0_SetCompareCallback(doNothing);
  SEI();
  // uint8 PWM_Percentage = 10;

  while(1) {
    // uint32 current = TMR0_Millis();

        // PWM_Percentage += (PWM_Percentage<100) ? 10 : -100;
        // TMR0_PWM(PWM_Percentage);
        TMR0_SetFrequency(2000);


  }
}