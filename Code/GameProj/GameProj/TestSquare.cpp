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
	mInput->BindAction("MoveRight", ActionState::Press, &TestSquare::MoveRight);

	mTexture = reinterpret_cast<RectangleTexture*>(Texture::CreateShape(Shapes::RectangleShape));
	mTexture->SetRectangle(10., 10.);
}

void TestSquare::Update(TimeSlotInSecond deltaSecond)
{

	mWalkVelocity.x = Math::Clamp(mWalkVelocity.x, -30.0f, 30.0f);
	mWalkVelocity.y = Math::Clamp(mWalkVelocity.y, -30.0f, 30.0f);

	mLocation += (mWalkVelocity * deltaSecond);
}

void TestSquare::Draw(ID2D1RenderTarget* renderTarget) const
{
	mTexture->Perform(renderTarget, Transform2D(NoScale, NoRotation, mLocation));
}

void TestSquare::MoveRightAxis(Percent percent)
{
	mWalkVelocity = 30.0f * percent;
}

void TestSquare::MoveRight()
{
	MoveRightAxis(1.0f);
	//Log::Print(LOG_DEBUG, "MoveRight");
}
