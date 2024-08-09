// Liuxijun


#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	// TODO
	SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadSlot::SetLoadSlotName(const FString& InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}
