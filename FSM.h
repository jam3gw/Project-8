#ifndef FSM_H_
#define FSM_H_

#include "debounce.h"
#include "LED_display.h"

// Type Definitions
typedef enum {AInactiveBInactive,AInactiveBActive,AActiveBInactive,AActiveBActive, ResetState} FSMState;

typedef struct {
    FSMState CurrentState;  // Current state of the FSM
    SwitchStatus SwitchA;   // Current input of the FSM
    SwitchStatus SwitchB;   // Current input of the FSM
    SwitchStatus Reset;   // Current input of the FSM
} FSMType;

// Function Prototypes
void InitializeFSM(FSMType *FSM);
FSMState NextStateFunction(FSMType *FSM);
void OutputFunction(FSMType *FSM);

#endif /* FSM_H_ */

