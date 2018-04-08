#pragma once
#include "Actor.h"
#include "IControllable.h"
#include "HIDInput.h"
#include "Texture.h"
#include "Transform.h"
#include "GameWorld.h"

class TestSquare :
	public Actor,
	public IControllable
{
public:
	TestSquare();
	~TestSquare();

	virtual void OnInitialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw(ID2D1RenderTarget* renderTarget) const override;

	virtual void ReceiveBehaviour(const InputInformations& strs) override;

	void MoveRight(Percent percent);

	void MoveUp(Percent percent);
private:
	HIDInput*				mInput;
	RectangleTexture*	mTexture;
	//Transform2D			mTransform;
	Translation2D			mLocation;
	Velocity2D				mWalkVelocity;
};

