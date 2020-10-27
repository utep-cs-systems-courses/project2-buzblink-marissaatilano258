#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char main_count = 0;
  if(++blink_count % 2 == 0) {
    if(button_state == 3){
      b3_state_machine();
    }
  }
  if(blink_count % 50 == 0){
    if(button_state == 2){
      b2_state_machine();
    }
  }
  if(blink_count==250) {
    switch(button_state){
    case 2:
      b2_state_advance();
      break;
    case 3:
      b3_state_advance();
      break;
    case 4:
      b4_state_advance();
    default:
      break;
    }
    blink_count = 0;
  }
  if(blink_count == 100){
    if(button_state == 1){
      b1_state_advance();
      blink_count = 0;
    }
  }
  if(blink_count == 75){
    if(button_state == 1){
      buzzer_set_period(0);
    }
  }
}
