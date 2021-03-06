#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char state = 0;
char button_state = 0;
static short siren_note = 0;
static char b1_state = 0;
static char b2_state = 0;
static char b3_state = 0;
static char b4_state = 0;
static char dim_state = 0;
static char siren_state = 0;

char on_on_off()
{
  char changed = 0;
  
  switch(state){
  case 0:
    red_on = 0;       /*Off*/
    green_on = 0;
    state++;
    changed = 1;
    break;
  case 1:
    red_on = 1;       /*On*/
    green_on = 1;
    state++;
    changed = 1;
    break;
  case 2:
    red_on = 1;       /*On*/
    green_on = 1;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

char off_off_on()
{
  char changed = 0;
  switch(state){
  case 0:
    red_on = 1;       /*On*/
    green_on = 1;
    state++;
    changed = 1;
    break;
  case 1:
    red_on = 0;       /*Off*/
    green_on = 0;
    state++;
    changed = 1;
    break;
  case 2:
    red_on = 0;       /*Off*/
    green_on = 0;
    state = 0;
    changed = 0;
    break;
  }
  return changed;
}

short go_up()
{
  siren_note += 225; /*Note rises by 250hz*/
  red_on = 1;
  green_on = 0;
  return 2000000/siren_note; /*note in hz = 2*10^6 / z */
}

short go_down()
{
  siren_note -= 450; /*Note falls by 450hz*/
  red_on = 0;
  green_on = 1;
  return 2000000/siren_note;/*note in hz = 2*10^6 / z*/
}

char toggle_led()
{
  if(red_on){
    red_on = 0;            /*Green on, Red off*/
    green_on = 1;
  } else {
    red_on = 1;            /*Green off, Red on*/
    green_on = 0;
  }
  return 1;
}

short pattern1()
{
  static char pattern1_state = 0;
  short note = 0;
  switch(pattern1_state){
  case 0:
    note = 659;           /* E */
    pattern1_state++;
    break;
  case 1:
    note = 587;           /* D */
    pattern1_state++;
    break;
  case 2:
    note = 523;           /* C */
    pattern1_state++;
    break;
  case 3:
    note = 587;           /* D */
    pattern1_state= 0;
    break;
  default:
    pattern1_state = 0;
    break;
  }
  return note;
}

short pattern2()
{
  static char pattern2_state = 0;
  short note = 0;
  switch(pattern2_state){
  case 0:
    note = 659;           /* E */
    pattern2_state++;
    break;
  case 1:
  case 2:
    note = 587;           /* D */
    pattern2_state++;
    break;
  case 3:
    note = 659;           /* E */
    pattern2_state++;
    break;
  case 4:
    note = 587;           /* D */
    pattern2_state++;
    break;
  case 5:
    note = 523;           /* C */
    pattern2_state = 0;
    break;
  default:
    pattern2_state = 0;
    break;
  }
  return note;
}

short b1_state_machine()
{
  short note = 0;
  switch(b1_state){
  case 0:
  case 1:
  case 2:
  case 3:
    note = pattern1();   /* E D C D*/
    break;
  case 4:
  case 5:
  case 6:
    note = 659;          /* E E E*/
    break;
  case 7:
    note = 0;            /* Pause */
    break;
  case 8:
  case 9:
  case 10:
    note = 587;          /*D D D */
    break;
  case 11:
    note = 0;            /* Pause */
    break;
  case 12:
  case 13:
  case 14:
    note = 659;          /* E E E */
    break;
  case 15:
    note = 0;            /* Pause */
    break;
  case 16:
  case 17:
  case 18:
  case 19:
    note = pattern1();   /* E D C D */
    break;
  case 20:
  case 21:
  case 22:
    note = 659;          /* E E E */
    break;
  case 23:
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
    note = pattern2();   /* E D E D C */
    break;
  case 29:
    note = 0;            /* Pause */
    break;
  default:
    b1_state = 0;
    break;
  }
  return 2000000/note;   /* note in hz = 2*10^6 / z */ 
}

void b2_state_machine()
{
  switch(siren_state){
  case 0:
  case 1:
    buzzer_set_period(go_up());      /*Increase for 2 periods */
    led_changed = 1;
    led_update();
    break;
  case 2:
    buzzer_set_period(go_down());    /*Decrease for 1 period */
    led_changed = 1;
    led_update();
    break;
  default:
    siren_state = 0;
    siren_note = 0;
    break;
  }
}

void b3_state_machine(){
  switch(dim_state){
  case 0:
    red_on = 1;                  /* 100% brightness */
    green_on = 1;
    led_changed = 1;
    led_update();
    break;
  case 1:
    led_changed = on_on_off();   /* 66% brightness */
    led_update();
    break;
  case 2:
    led_changed = off_off_on();  /* 33% brightness */
    led_update();
    break;
  default:
    dim_state = 0;
    break;
  }
}

short b4_state_machine()
{
  short note = 0;
  switch(b4_state){
  case 0:
    red_on = 0;
    green_on = 1;
    note = 587;
    break;
  case 1:
    red_on = 1;
    green_on = 0;
    note = 440;
    break;
  default:
    red_on = 0;          /*Turns off all leds and sounds*/
    green_on = 0;
    note = 0;
    break;
  }
  return 2000000/note;   /*notes in hz = 2*10^6 / z */
}

void button_state_advance()
{
  switch(button_state){
  case 1:
    b1_state = 0;       /*Resets state for state machine for Button S1*/
    break;
  case 2:               
    b2_state = 0;       /*Resets state for state machine for Button S2*/
    break;
  case 3:               
    b3_state = 0;       /*Resets state for state machine for Button S3*/
    break;
  case 4:               
    b4_state = 0;       /*Resets state for state machine for Button S4*/
    break;
  default:
    break;
  }
}

void b1_state_advance()
{
  led_changed = toggle_led();
  buzzer_set_period(b1_state_machine());
  led_update();
  b1_state++;
}

void b2_state_advance()
{
  siren_state++;
  b2_state_machine();
}

void b3_state_advance()
{
  buzzer_set_period(0);
  dim_state++;
  b3_state_machine();
}

void b4_state_advance()
{
  buzzer_set_period(b4_state_machine());
  led_changed = 1;
  led_update();
  b4_state++;
}
