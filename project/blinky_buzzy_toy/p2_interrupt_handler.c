#include <msp430.h>
#include "switches.h"

/* Switch on P1 (S2) */
/*P2IFG is a vector of flags that tells what caused an interrupt*/

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

