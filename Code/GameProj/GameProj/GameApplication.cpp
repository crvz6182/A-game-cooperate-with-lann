#include "stdafx.h"
#include "GameApplication.h"

GameApplication::GameApplication(HINSTANCE hInstance):
	DirectApplicationBase(hInstance),
	mD2DBackBufferRenderTarget(nullptr),
	mD2DFactory(nullptr),
	mDWriteFactory(nullptr),
	mWriteTextFormat(nullptr),
	mInput(nullptr),
	mWorld(nullptr),
	mSolidBrush(nullptr)
{
}

GameApplication::~GameApplication()
{
	ReleaseCOM(mSolidBrush);
	ReleaseCOM(mD2DFactory);
	ReleaseCOM(mD2DBackBufferRenderTarget);
	ReleaseCOM(mDWriteFactory);
	ReleaseCOM(mWriteTextFormat);

	GameWorld::DestroyWorld();
}

bool GameApplication::Initialize()
{
	if (!DirectApplicationBase::Initialize()) {
		return false;
	}
	if (!InitializeDirectInput()) {
		return false;
	}
	if (!InitializeDirect2D()) {
		return false;
	}
	mWorld = GameWorld::GetWorld();
	if (!mWorld->Initialize(mD2DBackBufferRenderTarget)) {
		return false;
	}
	return true;
}

void GameApplication::Update(TimeSlotInSecond deltaSecond)
{
	mInput->QueryInputs();
	mWorld->Update(deltaSecond);
}

void GameApplication::Draw()
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

	//绘制当前帧率信息
	if (mD2DBackBufferRenderTarget) {
		//开始绘图
		mD2DBackBufferRenderTarget->BeginDraw();
		D2D1_RECT_F rectRegion = D2D1::RectF(
			0., 0., 40., 20.
		);

		mD2DBackBufferRenderTarget->DrawText(String((int)(1 / mTimer.GetDeltaTime())), 4, mWriteTextFormat, rectRegion, mSolidBrush);
		
		mWorld->Perform();

		//结束绘图
		mD2DBackBufferRenderTarget->EndDraw();
	}

	//Sleep(16);
	mSwapChain->Present(0, 0);
}

void GameApplication::OnResize()
{
	ReleaseCOM(mSolidBrush);
	ReleaseCOM(mD2DBackBufferRenderTarget);
	ReleaseCOM(mD2DFactory);
	ReleaseCOM(mWriteTextFormat);
	ReleaseCOM(mDWriteFactory);

	DirectApplicationBase::OnResize();

	InitializeDirect2D();

	mWorld->SetRenderTarget(mD2DBackBufferRenderTarget);
}

bool GameApplication::InitializeDirectInput()
{
	mInput = HIDInput::GetHIDInput();
	return mInput->Initialize(GetApplicationInstance(), GetWindowHandler());
}

bool GameApplication::InitializeDirect2D()
{
	//获取交换链缓冲区
	IDXGISurface* backBuffer = nullptr;
	HR(mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)));

	//获取D2D工厂模式接口
	HR(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory));

	if (!mD2DFactory) {
		return false;
	}

	FLOAT dpiX;
	FLOAT dpiY;
	mD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	//创建渲染目标属性
	D2D1_RENDER_TARGET_PROPERTIES d2dRenderTargetProperties =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX, dpiY
		);
	//并使用创建的属性创建渲染目标
	HR(mD2DFactory->CreateDxgiSurfaceRenderTarget(backBuffer, &d2dRenderTargetProperties, &mD2DBackBufferRenderTarget));

	HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE::DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&mDWriteFactory)));

	HR(mDWriteFactory->CreateTextFormat(
		L"微软雅黑",
		nullptr,
		DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
		16,
		L"zh-CN",
		&mWriteTextFormat
	));
	ReleaseCOM(backBuffer);

	HR(mD2DBackBufferRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &mSolidBrush));

	return true;
}
