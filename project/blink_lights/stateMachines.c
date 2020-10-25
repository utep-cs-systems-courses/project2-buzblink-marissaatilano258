#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

unsigned short x = 500;
unsigned short sb = 0;
char state = 0;

char toggle_red()		/* always toggle! */
{
  //static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

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
    state = 1;
    changed = 1;
    break;
  case 1:
    red_on = 0;
    state = 2;
    changed = 1;
    break;
  case 2:
    red_on = 0;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}


char switch_colors()
{
  //static char state = 0;
  switch(state){
  case 0:
    red_on = 0;
    green_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 1;
    green_on = 0;
    state = 0;
    break;
  }
  return 1;
}

short twinkle_twinkle()
{
  short note = 0;
  switch(state){
  case 0:
    note = 698;
    red_on = 1;
    state = 1;
    break;
  case 1:
    note = 698;
    red_on = 0;
    state = 2;
    break;
  case 2:
    note = 523;
    red_on = 1;
    state = 3;
    break;
  case 3:
    note = 523;
    red_on = 0;
    state = 4;
    break;
  case 4:
    note = 587;
    red_on = 1;
    state = 5;
    break;
  case 5:
    note = 587;
    red_on = 0;
    state = 6;
    break;
  case 6:
    note = 523;
    red_on = 1;
    state = 7;
    break;
  case 7:
    note = 0;
    red_on = 0;
    state = 7;
    break;
  }
  return note;
}

void buzzer_advance()
{
  if(sb){
    x+=225;
  } else {
    x-=450;
  }
  short y = 2000000/x;
  buzzer_set_period(y);
}

void go_down()
{
  sb = 0;
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}

void go_up()
{
  sb = 1;
  red_on = 0;
  green_on = 1;
  led_changed = 1;
  led_update();
}

void main_state_advance()
{
  //static char state = 0;
  switch(state){
  case 0:
  case 1:
    go_up();
    state++;
    break;
  case 2:
    go_down();
    state = 0;
    break;
  }
}

void state_advance()		/* alternate between toggling red & green */
{
  led_changed = 1;
  led_update();
  buzzer_set_period(twinkle_twinkle());
  /*
  char changed = 0;  

  static enum {R=0, G=1} color = R;
  switch (color) {
  case R: changed = toggle_red(); color = R;break;
  case G: changed = toggle_green(); color = R;break;
  }

  led_changed = changed;
  led_update();
  */
  /*
  static char led_dim_state = 0;
  switch(led_dim_state){
  case 0:
    led_changed = toggle_red();
    led_dim_state = 1;
    break;
  case 1:
    led_changed = on_on_off();
    led_dim_state = 2;
    break;
  case 2:
    led_changed = off_off_on();
    led_dim_state = 0;
    break;
  }
  
  led_update();
  */
}



