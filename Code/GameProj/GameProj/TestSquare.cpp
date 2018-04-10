#include "stdafx.h"
#include "TestSquare.h"


TestSquare::TestSquare():
	mInput(nullptr),
	mTexture(nullptr)
{
	mLocation = { 50,100 };

	mWalkVelocity = { 0,0 };
}


TestSquare::~TestSquare()
{
	delete mTexture;
}

void TestSquare::OnInitialize()
{
	mInput = HIDInput::GetHIDInput();

	mTexture = reinterpret_cast<RectangleTexture*>(Texture::CreateShape(Shapes::RectangleShape));
	mTexture->SetRectangle(10., 10.);
}

void TestSquare::Update(TimeSlotInSecond deltaSecond)
{
	ReceiveBehaviour(mInput->GetBehaviours());
	mWalkVelocity.x = Math::Clamp(mWalkVelocity.x, -30.0f, 30.0f);
	mWalkVelocity.y = Math::Clamp(mWalkVelocity.y, -30.0f, 30.0f);

	mLocation += (mWalkVelocity * deltaSecond);
	mWalkVelocity = { 0, 0 };
}

void TestSquare::Draw(ID2D1RenderTarget* renderTarget) const
{
	mTexture->Perform(renderTarget, Transform2D(NoScale, NoRotation, mLocation));
}

void TestSquare::ReceiveBehaviour(const InputInformations & strs)
{
	for (auto pair : strs) {
		if (pair.GetFirst() == "MoveRight") {
			//MoveRight(pair.GetSecond());
		}
		
		if (pair.GetFirst() == "MoveLeft") {
			//MoveRight(-pair.GetSecond());
		}

		if (pair.GetFirst() == "MoveUp") {
			//MoveUp(pair.GetSecond());
		}

		if (pair.GetFirst() == "MoveDown") {
			//MoveUp(-pair.GetSecond());
		}
	}
}

void TestSquare::MoveRight(Percent percent)
{
	if (percent == ActionState::Release && mWalkVelocity.x == 30.0f) {
		mWalkVelocity.x = 0;
		return;
	}
	mWalkVelocity.x = 30.0f;
}

void TestSquare::MoveUp(Percent percent)
{
	if (percent == ActionState::Release && mWalkVelocity.y == 30.0f) {
		mWalkVelocity.y = 0;
		return;
	}
	mWalkVelocity.y = -30.0f;
}
