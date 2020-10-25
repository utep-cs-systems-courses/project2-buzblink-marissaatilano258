#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

unsigned short x = 500;
unsigned short sb = 0;
char state = 0;
char button_state = 0;
static char b1_state = 0;
static char b2_state = 0;
static char b3_state = 0;
static char b4_state = 0;
static char dim_state = 0;

char on_on_off()
{
  //static char state = 0;
  char changed = 0;
  
  switch(state){
  case 0:
    red_on = 0;
    state = 1;
    changed = 1;
    break;
  case 1:
    red_on = 1;
    state = 2;
    changed = 1;
    break;
  case 2:
    red_on = 1;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

char off_off_on()
{
  //static char state = 0;
  char changed = 0;
  switch(state){
  case 0:
    red_on = 1;
    green_on = 1;
    state = 1;
    changed = 1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    state = 2;
    changed = 1;
    break;
  case 2:
    red_on = 0;
    green_on = 1;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

short b1_state_machine()
{
  short note = 0;
  switch(b1_state){
  case 0:
    note = 698;
    red_on = 1;
    b1_state = 1;
    break;
  case 1:
    note = 698;
    red_on = 0;
    b1_state = 2;
    break;
  case 2:
    note = 523;
    red_on = 1;
    b1_state = 3;
    break;
  case 3:
    note = 523;
    red_on = 0;
    b1_state = 4;
    break;
  case 4:
    note = 587;
    red_on = 1;
    b1_state = 5;
    break;
  case 5:
    note = 587;
    red_on = 0;
    b1_state = 6;
    break;
  case 6:
    note = 523;
    red_on = 1;
    b1_state = 7;
    break;
  case 7:
    note = 0;
    red_on = 0;
    b1_state = 7;
    button_state = 0;
    break;
  }
  return note;
}

short b2_state_machine()
{
  static char x = 0;
  switch(b2_state){
  case 0:
    x += 500;
    green_on = 1;
    red_on = 0;
    b2_state = 1;
    break;
  case 1:
    x-=200;
    green_on = 0;
    red_on = 1;
    b2_state = 2;
    break;
  case 2:
    x = 0;
    green_on=0;
    red_on = 0;
    button_state = 0;
    break;
  }
  return x;
}

void b3_state_machine(){
  switch(dim_state){
  case 0:
    red_on = 1;
    led_changed = 1;
    led_update();
    break;
  case 1:
    led_changed = on_on_off();
    led_update();
    break;
  case 2:
    led_changed = off_off_on();
    led_update();
    break;
  default:
    dim_state = 0;
    break;
  }
}

void button_state_advance()
{
  switch(button_state){
  case 1:
    b1_state = 0;
    break;
  case 2:               /*Button S2*/
    b2_state = 0;
    break;
  case 3:               /*Button S3*/
    b3_state = 0;
    break;
  case 4:               /*Button S4*/
    b4_state = 0;
    break;
  default:
    break;
  }
}

void b1_state_advance()
{
  led_changed = 1;
  buzzer_set_period(b1_state_machine());
  led_update();
}

void b2_state_advance()
{
  led_changed = 1;
  buzzer_set_period(b2_state_machine());
  led_update();
}

void b3_state_advance()
{
  dim_state++;
  b3_state_machine();
}
