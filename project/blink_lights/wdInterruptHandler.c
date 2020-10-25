#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(++blink_count==200) {
    if(button_state == 1){
      b1_state_advance();
    }else if(button_state == 2){
      b2_state_advance();
    }
    blink_count = 0;
  }else if(blink_count == 175){
    buzzer_set_period(0);
  }

  //Siren practice
  /*
  if(++count == 25){
    buzzer_advance();
    count = 0;
  }
  if(++main_count == 250){
    main_state_advance();
    main_count = 0;
  }
  */
}
