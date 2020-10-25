#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(++blink_count==200) {
    state_advance();
    //buzzer_set_period(1000);
    blink_count = 0;
  } else if(blink_count == 175){
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
