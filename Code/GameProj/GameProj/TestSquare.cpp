#include "stdafx.h"
#include "TestSquare.h"


TestSquare::TestSquare():
	mInput(nullptr),
	mTexture(nullptr)
{
	mLocation.x = 50;
	mLocation.y = 100;

	mVelocity.x = 0;
	mVelocity.y = 0;
}


TestSquare::~TestSquare()
{
}

void TestSquare::OnInitialize()
{
	mInput = HIDInput::GetHIDInput();
	mTexture = reinterpret_cast<RectangleTexture*>(Texture::CreateShape(Shapes::RectangleShape));
	mTexture->SetRectangle(10., 10.);
}

void TestSquare::Update(TimeSlotInSecond deltaSecond)
{
	if (mInput->GetKeyState(DIK_D)) {
		mVelocity.x = 30;
	}
	else {
		mVelocity.x = 0;
	}
	
	mLocation += (mVelocity * deltaSecond);
}

void TestSquare::Draw(ID2D1RenderTarget* renderTarget) const
{
	mTexture->Perform(renderTarget, Transform2D(NoScale, NoRotation, mLocation));
}
