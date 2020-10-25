#ifndef stateMachine_included
#define stateMachine_included

void buzzer_advance();
void button_state_advance();
void b1_state_advance();
void b2_state_advance();
void b3_state_advance();
void b4_state_advance();

extern char state, button_state;

#endif // included
