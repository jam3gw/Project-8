#include "debounce.h"

#define FALSE 0
#define TRUE 1

extern unsigned int g1msTimer;

void InitializeSwitch(SwitchDefine *Switch,char *SwitchPort,unsigned char SwitchBit,
		SwitchStatus Logic0Value, SwitchStatus Logic1Value,
		unsigned char ActiveThreshold,unsigned char InactiveThreshold)
{
	Switch->CurrentState = WaitingForActive;
	Switch->SwitchPort = SwitchPort;
	Switch->SwitchPortBit = SwitchBit;
	Switch->Logic0Value = Logic0Value;
	Switch->Logic1Value = Logic1Value;

	Switch->ActiveThreshold = ActiveThreshold; // units equal milliseconds
	Switch->InactiveThreshold = InactiveThreshold; // units equal milliseconds
	Switch->EventTime = 0;
	Switch->DebouncedSwitchStatus = Inactive;
	Switch->SwitchCycleNotComplete = TRUE;
}

SwitchStatus ReadSwitchStatus(SwitchDefine *Switch)
{
	volatile unsigned char SwitchValue;

	SwitchValue = *(Switch->SwitchPort) & Switch->SwitchPortBit;
	if (SwitchValue)
		return Switch->Logic1Value;
	else
		return Switch->Logic0Value;
}

DbState NextStateFunctionDebounce(SwitchDefine *Switch,unsigned char X0,unsigned char X1)
{
	DbState NextState;

	switch (Switch->CurrentState) {
		case WaitingForActive:
			if (X0 == TRUE) {NextState = ValidateActive;}
			else {NextState = WaitingForActive;}
		break;
		case ValidateActive:
			if (X0 == FALSE) {NextState = WaitingForActive;}
			else {
				if (X1 == TRUE) {NextState = WaitingForInactive;}
				else {NextState = ValidateActive;}
			}
		break;
		case WaitingForInactive:
			if (X0 == FALSE) {NextState = ValidateInactive;}
			else {NextState = WaitingForInactive;}
		break;
		case ValidateInactive:
			if (X0 == TRUE) {NextState = WaitingForInactive;}
			else {
				if (X1 == TRUE) {NextState = WaitingForActive;}
				else {NextState = ValidateInactive;}
			}
		break;
		default: NextState = WaitingForActive;
	}
	
	return NextState;
}

void OutputFunctionDebounce(SwitchDefine *Switch,unsigned char X0,unsigned char X1)
{
	switch (Switch->CurrentState) {
		case WaitingForActive:
			if (X0 == TRUE) { Switch->EventTime = g1msTimer; }
			Switch->DebouncedSwitchStatus = Inactive;
		break;
		case ValidateActive:
			if ((X1 == TRUE) && (X0 == TRUE)) {Switch->DebouncedSwitchStatus = Active;}
			else {Switch->DebouncedSwitchStatus = Inactive;}
		break;
		case WaitingForInactive:
			if (X0 == FALSE) { Switch->EventTime = g1msTimer; }
			Switch->DebouncedSwitchStatus = Active;
		break;
		case ValidateInactive:
			if ((X1 == TRUE) && (X0 == FALSE)) {
			    Switch->DebouncedSwitchStatus = Inactive;
			    Switch->SwitchCycleNotComplete = FALSE;
			}
			else {Switch->DebouncedSwitchStatus = Active;}
		break;
		//default: ;
	}
}
