#pragma once
#include "Actor.h"
#include "HIDInput.h"
#include "Texture.h"
#include "Transform.h"
#include "GameWorld.h"
#include "Log.h"

class TestSquare :
	public Actor
{
public:
	TestSquare();
	~TestSquare();

	virtual void OnInitialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw(ID2D1RenderTarget* renderTarget) const override;

	void MoveRightAxis(Percent percent);

	void MoveRight();
private:
	HIDInput*				mInput;
	RectangleTexture*	mTexture;
	//Transform2D			mTransform;
	Translation2D			mLocation;
	Velocity2D				mWalkVelocity;
};

