#pragma once
#include "String.h"

__interface IStringPerformable
{
	virtual String ToString() const { return L"No defined string performation."; }
};