## Description
This interrupt-driven program produces different sequences based on the button
that is pushed, including flashing the LEDs and buzzing the buzzer.

Press S1, and the green and red leds toggle while the buzzer plays Mary Had a
Little Lamb

Press S2, and the red and green light will indicate a rise and fall produced
by the siren sound

Press S3, and the red and green led will dim and brighten

Press S4, the flashing of the leds and buzzer will inidicate the termination
of leds and sounds

## Files

The following files are included in this program.
File | Description
-----------------------| -----------
buzzer.c               | Intializes the buzzer and sets the period for buzzer cycles
buzzer.h               | Header file containing all declarations of methods in buzzer.h
led.c                  | Initialize leds and defines a function to update the state of each led
led.h                  | Header file containing all declarations of methods in led.c
p2_interrupt_handler.c | Handles interrupts that occur on P2 of the MSP430
stateMachines.c        | Defines all state machines used to flash leds andplay songs
stateMachines.h        | Header file containing all declarations of methods in stateMachines.c
switches.c             | Initializes switches, updates switch interrupt sense,
corresponds interrupt to state machine.
switches.h             | Header file containing all declarations of methods in switches.c
toyMain.c              | Configures clocks, intializes leds, buzzer, switches,
and enables interrupts
wdInterruptHandler.c   | Watch Dog Timer used to control interrupts for state
machine advances

## Complile and Run
You can compile this program by using the commands
    $make clean
    $make all
Next plug in your MSP430 to linux
The following command runs the program
    $make load
Use the buttons on the green board of the MSP430 to use the functions of the program








