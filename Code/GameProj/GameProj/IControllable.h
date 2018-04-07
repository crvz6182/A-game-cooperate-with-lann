#pragma once
#include "Math.h"
#include "String.h"
#include "HIDInput.h"

__interface IControllable
{
public:
	virtual void ReceiveBehaviour(const InputInformations& strs) = 0;
};