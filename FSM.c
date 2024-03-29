# include "FSM.h"
#include "pwm.h"
#include "LED.h"
//#include "InterruptServiceRoutines.h"

extern unsigned int g1msTimer;
extern volatile int RotaryEncoderStateCount;
extern int LEDDisplayValue;

void InitializeFSM(FSMType *FSM)
{
    FSM->CurrentState = ResetState;

    //Initialization of the motor
    //Standby
    P1DIR |= BIT1;
    P1OUT |= BIT1;


    //PWM
    P1DIR |= BIT2;
    P1OUT |= BIT2;


    //In1
    P1DIR |= BIT3;
    P1OUT |= BIT3;


    //In2
    P1DIR |= BIT4;
    P1OUT &= ~BIT4;
}

FSMState NextStateFunction(FSMType *FSM)
{
    volatile FSMState NextState;

    switch (FSM->CurrentState) {
    case ResetState:
        if (FSM->Reset == Active){
            NextState = ResetState;
        }
        else if ((FSM->SwitchA == Active)&& (FSM->SwitchB == Active)){
            NextState = AActiveBActive;
        }
        else if ((FSM->SwitchA == Inactive)&& (FSM->SwitchB == Active)){
            NextState = AInactiveBActive;
        }
        else if ((FSM->SwitchA == Active)&& (FSM->SwitchB == Inactive)){
            NextState = AActiveBInactive;
        }
        else if ((FSM->SwitchA == Inactive)&& (FSM->SwitchB == Inactive)){
            NextState = AInactiveBInactive;
        }
        break;

    case AInactiveBInactive:
        if (FSM->Reset == Active){
            NextState = ResetState;
        }
        else if (FSM->SwitchA == Active){
            NextState = AActiveBInactive;
        }
        else if (FSM->SwitchB == Active){
            NextState = AInactiveBActive;
        } else{
            NextState = AInactiveBInactive;
        }
        break;

    case AInactiveBActive:
        if (FSM->Reset == Active){
            NextState = ResetState;
        }
        else if (FSM->SwitchA == Active){
            NextState = AActiveBActive;
        }
        else if (FSM->SwitchB == Inactive){
            NextState = AInactiveBInactive;
        } else {
            NextState = AInactiveBActive;
        }
        break;

    case AActiveBInactive:
        if (FSM->Reset == Active){
            NextState = ResetState;
        }
        else if (FSM->SwitchB == Active){
            NextState = AActiveBActive;
        }
        else if (FSM->SwitchA == Inactive){
            NextState = AInactiveBInactive;
        } else {
            NextState = AActiveBInactive;
        }
        break;

    case AActiveBActive:
        if (FSM->Reset == Active){
            NextState = ResetState;
        }
        else if (FSM->SwitchB == Inactive){
            NextState = AActiveBInactive;
        }
        else if (FSM->SwitchA == Inactive){
            NextState = AInactiveBActive;
        } else {
            NextState = AActiveBActive;
        }
        break;

    default:
        NextState = ResetState;
    }

    return NextState;
}

void OutputFunction(FSMType *FSM)
{
    // Update RotaryEncoderStateCount
    switch (FSM->CurrentState) {
    case ResetState:
        RotaryEncoderStateCount = 0;
        break;
    case AInactiveBInactive:
        if (FSM->SwitchA == Active){
            RotaryEncoderStateCount++;
        }
        else if (FSM->SwitchB == Active){
            RotaryEncoderStateCount--;
        }
        break;
    case AInactiveBActive:
        if (FSM->SwitchA == Active){
            RotaryEncoderStateCount--;
        }
        else if (FSM->SwitchB == Inactive){
            RotaryEncoderStateCount++;
        }
        break;
    case AActiveBInactive:
        if (FSM->SwitchB == Active){
            RotaryEncoderStateCount++;
        }
        else if (FSM->SwitchA == Inactive){
            RotaryEncoderStateCount--;
        }
        break;
    case AActiveBActive:
        if (FSM->SwitchB == Inactive){
            RotaryEncoderStateCount--;
        }
        else if (FSM->SwitchA == Inactive){
            RotaryEncoderStateCount++;
        }
        break;
    default:
        RotaryEncoderStateCount = 0;
    }

    // Now, use RotaryEncoderStateCount to update the value of TA0CCR1 to modify the PWM duty cycle
    // and update the corresponding value displayed in the two 7-segment displays.
    if (FSM->CurrentState == ResetState) {
        // Insert code to initialize TA0CCR1 and the LED display value.
        LEDDisplayValue = 5;
        //TA0CCR1 = (TA0CCR0 >> 1);
    }
    else {
        volatile int count = RotaryEncoderStateCount;
        if (RotaryEncoderStateCount == 48) { // clockwise
            // Insert code action(s) when rotary encoder has been rotated clockwise.
            TOGGLE_GREEN_LED;
            if (g1msTimer > SET_POINT){
                TA0CCR1 += 1;
            }
            else if (g1msTimer < SET_POINT){
                TA0CCR1 -= 1;
            }

            RotaryEncoderStateCount = 0;
            g1msTimer = 0;

        }

        if (RotaryEncoderStateCount == -48) { // counter-clockwise
            // Insert code for action(s) when rotary encoder has been rotated counter-clockwise.
            TOGGLE_GREEN_LED;
            if (g1msTimer > SET_POINT){
                TA0CCR1 += 1;
            }
            else if (g1msTimer < SET_POINT){
                TA0CCR1 -= 1;
            }

            RotaryEncoderStateCount = 0;
            g1msTimer = 0;
        }
    }
    SetLEDDisplay(LEDDisplayValue);
}
