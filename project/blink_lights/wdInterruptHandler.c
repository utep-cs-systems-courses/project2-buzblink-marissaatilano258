#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(++blink_count==125) {
    state_advance();
    //buzzer_set_period(1000);
    blink_count = 0;
  }
}
