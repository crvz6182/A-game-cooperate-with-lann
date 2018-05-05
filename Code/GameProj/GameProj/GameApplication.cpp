#include "stdafx.h"
#include "GameApplication.h"

GameApplication::GameApplication(HINSTANCE hInstance):
	DirectApplicationBase(hInstance)
{
}

GameApplication::~GameApplication()
{
	delete mGameWorld;
	mInput->DestroyHIDInput();
}

bool GameApplication::Initialize()
{
	if (!DirectApplicationBase::Initialize()) {
		return false;
	}

	if (!InitializeDirectInput()) {
		return false;
	}

	Log::RegisterDirectApplication(this);

	mGameWorld = new GameWorld();

	mGameWorld->Initialize();

	return true;
}

void GameApplication::Update(TimeSlotInSecond deltaSecond)
{
	mInput->QueryInputsThenCallBack();
	mGameWorld->Update(deltaSecond);
}

/*void GameApplication::Draw()
{
	//指定背景色清空渲染对象视图
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	r += 0.8f;
	g += 0.6f;
	b += 0.4f;

	float bgColor[] = { r, g, b, 1.0f };
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, bgColor);
	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Sleep(16);
	mSwapChain->Present(0, 0);
}*/

void GameApplication::OnResize()
{
	DirectApplicationBase::OnResize();
}

bool GameApplication::InitializeDirectInput()
{
	mInput = HIDInput::GetHIDInput();
	return mInput->Initialize(GetApplicationInstance(), GetWindowHandler());
}
