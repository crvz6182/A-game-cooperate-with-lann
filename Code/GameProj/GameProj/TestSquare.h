#pragma once
#include "Actor.h"
#include "HIDInput.h"
#include "Texture.h"
#include "Transform.h"
#include "GameWorld.h"

class TestSquare :
	public Actor
{
public:
	TestSquare();
	~TestSquare();

	virtual void OnInitialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw(ID2D1RenderTarget* renderTarget) const override;
private:
	HIDInput*				mInput;
	RectangleTexture*	mTexture;
	//Transform2D			mTransform;
	Translation2D			mLocation;
	Velocity2D				mVelocity;
};

