#include "stdafx.h"
#include "DirectApplicationBase.h"


DirectApplicationBase::DirectApplicationBase(HINSTANCE hInstance):
	WindowApplicationBase(hInstance),
	mTimer(),
	mDevice(nullptr),
	mImmediateContext(nullptr),
	mSwapChain(nullptr),
	mMsaaQualityLevels(-1),
	mRenderTargetView(nullptr),
	mDepthStencilView(nullptr),
	mDepthStencilBuffer(nullptr),
	mD2DBackBufferRenderTarget(nullptr),
	mD2DFactory(nullptr),
	mDWriteFactory(nullptr),
	mWriteTextFormat(nullptr),
	mSolidBrush(nullptr),
	mInput(nullptr)
{
	mActorLocation.x = 100;
	mActorLocation.y = 200;
}


DirectApplicationBase::~DirectApplicationBase()
{
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSwapChain);

	ReleaseCOM(mD2DFactory);
	ReleaseCOM(mD2DBackBufferRenderTarget);
	ReleaseCOM(mDWriteFactory);
	ReleaseCOM(mWriteTextFormat);
	ReleaseCOM(mSolidBrush);

	ReleaseCOM(mDepthStencilBuffer);

	HIDInput::DestroyHIDInput();

	//复位所有默认设置
	if (mImmediateContext) {
		mImmediateContext->ClearState();
	}

	ReleaseCOM(mImmediateContext);

#if defined (DEBUG) || (_DEBUG)
	ID3D11Debug* d3dDebug = 0;
	HRESULT hr = mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
	if (SUCCEEDED(hr)) {
		hr = d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
	ReleaseCOM(d3dDebug);
#endif

	ReleaseCOM(mDevice);
}

bool DirectApplicationBase::Initialize()
{
	if (!WindowApplicationBase::Initialize()) {
		return false;
	}
	if (!InitializeDirect()) {
		return false;
	}
	return true;
}

int DirectApplicationBase::RunApplication()
{
	MSG msg = { 0 };
	mTimer.ResetTimer();
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			mTimer.Tick();
			Update(mTimer.GetDeltaTime());
			Draw();
		}
	}
	return msg.wParam;
}

void DirectApplicationBase::Update(TimeSlotInSecond deltaTime)
{
	static TimeSlotInSecond	lastTimeUpdated = 0.0f;
	lastTimeUpdated += deltaTime;
	if (lastTimeUpdated < (1.0f/60.0f)) {
		return;
	}
	lastTimeUpdated = 0.0f;
	mInput->QueryInputs();
	if (mInput->GetKeyState(DIK_D)) {
		mActorLocation.x += 1;
	}
}

void DirectApplicationBase::Draw()
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

		D2D1_RECT_F actorRegion = D2D1::RectF(
			mActorLocation.x, mActorLocation.y, mActorLocation.x+10, mActorLocation.y+10
		);
		mD2DBackBufferRenderTarget->DrawRectangle(actorRegion, mSolidBrush);
		//结束绘图
		mD2DBackBufferRenderTarget->EndDraw();
	}


	//Sleep(16);
	mSwapChain->Present(0, 0);
}

void DirectApplicationBase::OnResize()
{
	assert(mImmediateContext);
	assert(mDevice);
	assert(mSwapChain);

	//释放成员变量持有的旧视图和缓冲区
	//以新的窗体宽高重新创建

	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mDepthStencilBuffer);

	ReleaseCOM(mD2DBackBufferRenderTarget);
	ReleaseCOM(mD2DFactory);
	ReleaseCOM(mDWriteFactory);
	ReleaseCOM(mWriteTextFormat);
	ReleaseCOM(mSolidBrush);

	//重新缩放渲染对象视图

	HR(mSwapChain->ResizeBuffers(1, mWindowSize.Width, mWindowSize.Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(mDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	ReleaseCOM(backBuffer);


	//确保MSAA质量等级可用
	QueryMsaaQualityLevel();

	//创建新的深度模板视图和深度模板缓冲区
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = mWindowSize.Width;
	depthStencilDesc.Height = mWindowSize.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (true) {				//Enable MSAA
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = mMsaaQualityLevels - 1;
	}
	else {
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(mDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(mDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));

	//重新将新的渲染对象视图和深度模板视图绑定到流水线
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//重新设定窗口视窗

	D3D11_VIEWPORT screenViewPort;
	screenViewPort.TopLeftX = 0;
	screenViewPort.TopLeftY = 0;
	screenViewPort.Width = static_cast<float>(mWindowSize.Width);
	screenViewPort.Height = static_cast<float>(mWindowSize.Height);
	screenViewPort.MinDepth = 0.0f;
	screenViewPort.MaxDepth = 1.0f;

	mImmediateContext->RSSetViewports(1, &screenViewPort);

	InitializeDirect2D();
}

void DirectApplicationBase::Pause()
{
	mTimer.PauseTimer();
}

void DirectApplicationBase::Resume()
{
	mTimer.ResumeTimer();
}

bool DirectApplicationBase::InitializeDirect()
{
	UINT createDeviceFlag = D3D10_CREATE_DEVICE_BGRA_SUPPORT;
	//若是在调试模式下，则以调试模式创建设备
#if defined(DEBUG) || defined (_DEBUG)
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//创建设备，并检测feature level
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		createDeviceFlag,
		0, 0,
		D3D11_SDK_VERSION,
		&mDevice,
		&featureLevel,
		&mImmediateContext
	);

	if (FAILED(hr)) {
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	//确保MSAA质量等级可用
	QueryMsaaQualityLevel();

	//创建交换链所需的参数描述
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDescription;

	dxgiSwapChainDescription.BufferDesc.Width = mWindowSize.Width;
	dxgiSwapChainDescription.BufferDesc.Height = mWindowSize.Height;
	dxgiSwapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dxgiSwapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (true) {				//Enable MSAA
		dxgiSwapChainDescription.SampleDesc.Count = 4;
		dxgiSwapChainDescription.SampleDesc.Quality = mMsaaQualityLevels - 1;
	}
	else {
		dxgiSwapChainDescription.SampleDesc.Count = 1;
		dxgiSwapChainDescription.SampleDesc.Quality = 0;
	}

	dxgiSwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDescription.BufferCount = 1;
	dxgiSwapChainDescription.OutputWindow = mMainWIndowHandler;
	dxgiSwapChainDescription.Windowed = true;
	dxgiSwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	dxgiSwapChainDescription.Flags = 0;

	//必须使用 被用来创建当前设备 的工厂 来创建相匹配的交换链
	//否则设备与交换链不匹配
	IDXGIDevice* dxgiDevice = nullptr;
	HR(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = nullptr;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = nullptr;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(mDevice, &dxgiSwapChainDescription, &mSwapChain));

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	InitializeDirectInput();

	OnResize();

	return true;
}

bool DirectApplicationBase::InitializeDirectInput()
{
	mInput = HIDInput::GetHIDInput();
	return mInput->Initialize(GetApplicationInstance(), GetWindowHandler());
}

bool DirectApplicationBase::InitializeDirect2D()
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

	HR(mD2DBackBufferRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &mSolidBrush));

	ReleaseCOM(backBuffer);

	return true;
}

void DirectApplicationBase::QueryMsaaQualityLevel()
{
	//只需要查询一次MSAA质量等级
	if (mMsaaQualityLevels != -1) {
		return;
	}

	//检测4xMSAA支持的质量等级
	//只要是支持D3D11的设备一定支持4xMSAA，
	//因此只需要检测支持的质量等级即可
	HR(mDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &mMsaaQualityLevels));
	assert(mMsaaQualityLevels > 0);
}

void DirectApplicationBase::Windowize()
{
	if (!mDevice) {
		return;
	}
	WindowApplicationBase::Windowize();
}

