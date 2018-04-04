#pragma once
#include "IStringPerformable.h"
#include "./DirectUtility.h"
#include "Timer.h"

class Actor : public IStringPerformable
{
public:

	virtual void OnInitialize() = 0;

	virtual void Update(TimeSlotInSecond deltaSecond) = 0;

	virtual void Draw(ID2D1RenderTarget* renderTarget) const = 0;
	
	virtual String ToString() const override { return L"Actor"; }
};
