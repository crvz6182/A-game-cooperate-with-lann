#include "stdafx.h"
#include "DirectApplicationBase.h"

using namespace D3DUtil;

DirectApplicationBase::DirectApplicationBase(HINSTANCE hInstance):
	WindowApplicationBase(hInstance),
	mTimer(),
	mMsaaQualityLevels(0),
	/*gD3dDevice(nullptr),
	gImmediateDeviceContext(nullptr),
	gSwapChain(nullptr),
	gRenderTargetView(nullptr),
	gDepthStencilView(nullptr),*/
	mDepthStencilBuffer(nullptr),
	mVideoSettingConfig("Resource\\Config\\VideoSettings.json")
{
}


DirectApplicationBase::~DirectApplicationBase()
{
	ReleaseCOM(gRenderTargetView);
	ReleaseCOM(gDepthStencilView);
	ReleaseCOM(gSwapChain);

	ReleaseCOM(mDepthStencilBuffer);


	//复位所有默认设置
	if (gImmediateDeviceContext) {
		gImmediateDeviceContext->ClearState();
	}

	ReleaseCOM(gImmediateDeviceContext);

#if defined (DEBUG) || (_DEBUG)
	ID3D11Debug* d3dDebug = 0;
	HRESULT hr = gD3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
	if (SUCCEEDED(hr)) {
		hr = d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
	ReleaseCOM(d3dDebug);
#endif

	ReleaseCOM(gD3dDevice);
}

bool DirectApplicationBase::Initialize()
{
	mVideoSettingConfig.GetConfig();
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
		}
	}
	return (int)msg.wParam;
}

void DirectApplicationBase::OnResize()
{
	assert(gImmediateDeviceContext);
	assert(gD3dDevice);
	assert(gSwapChain);

	//释放成员变量持有的旧视图和缓冲区
	//以新的窗体宽高重新创建

	ReleaseCOM(gRenderTargetView);
	ReleaseCOM(gDepthStencilView);
	ReleaseCOM(mDepthStencilBuffer);

	//重新缩放渲染对象视图

	HR(gSwapChain->ResizeBuffers(1, (UINT)mVideoSettingConfig.GetResolution().Width, (UINT)mVideoSettingConfig.GetResolution().Height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
	ID3D11Texture2D* backBuffer;
	HR(gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(gD3dDevice->CreateRenderTargetView(backBuffer, 0, &gRenderTargetView));
	ReleaseCOM(backBuffer);


	//确保MSAA质量等级可用
	QueryMsaaQualityLevel();

	//创建新的深度模板视图和深度模板缓冲区
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = (UINT)mVideoSettingConfig.GetResolution().Width;
	depthStencilDesc.Height = (UINT)mVideoSettingConfig.GetResolution().Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (mVideoSettingConfig.GetIsAntiAlias()) {				//Enable MSAA
		depthStencilDesc.SampleDesc.Count = mVideoSettingConfig.GetAntiAliasLevel();
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

	HR(gD3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(gD3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &gDepthStencilView));

	//重新将新的渲染对象视图和深度模板视图绑定到流水线
	gImmediateDeviceContext->OMSetRenderTargets(1, &gRenderTargetView, gDepthStencilView);

	//重新设定窗口视窗

	D3D11_VIEWPORT screenViewPort;
	screenViewPort.TopLeftX = 0;
	screenViewPort.TopLeftY = 0;
	screenViewPort.Width = static_cast<FLOAT>(mVideoSettingConfig.GetResolution().Width);
	screenViewPort.Height = static_cast<FLOAT>(mVideoSettingConfig.GetResolution().Height);
	screenViewPort.MinDepth = 0.0f;
	screenViewPort.MaxDepth = 1.0f;

	gImmediateDeviceContext->RSSetViewports(1, &screenViewPort);

}

void DirectApplicationBase::Pause()
{
	mTimer.PauseTimer();
}

void DirectApplicationBase::Resume()
{
	mTimer.ResumeTimer();
}

TimeSlotInSecond DirectApplicationBase::GetGameTime() const
{
	return mTimer.GetTotalValidTime();
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
		&gD3dDevice,
		&featureLevel,
		&gImmediateDeviceContext
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

	dxgiSwapChainDescription.BufferDesc.Width = (UINT)mVideoSettingConfig.GetResolution().Width;
	dxgiSwapChainDescription.BufferDesc.Height = (UINT)mVideoSettingConfig.GetResolution().Height;
	dxgiSwapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	dxgiSwapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (mVideoSettingConfig.GetIsAntiAlias()) {				//Enable MSAA
		dxgiSwapChainDescription.SampleDesc.Count = mVideoSettingConfig.GetAntiAliasLevel();
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
	HR(gD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = nullptr;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = nullptr;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(gD3dDevice, &dxgiSwapChainDescription, &gSwapChain));

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	DirectApplicationBase::OnResize();

	return true;
}

void DirectApplicationBase::QueryMsaaQualityLevel()
{
	//只需要查询一次MSAA质量等级
	if (mMsaaQualityLevels != 0) {
		return;
	}

	//检测4xMSAA支持的质量等级
	//只要是支持D3D11的设备一定支持4xMSAA，
	//因此只需要检测支持的质量等级即可
	HR(gD3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, mVideoSettingConfig.GetAntiAliasLevel(), &mMsaaQualityLevels));
	assert(mMsaaQualityLevels > 0);
}

void DirectApplicationBase::Windowize()
{
	if (!gD3dDevice) {
		return;
	}
	WindowApplicationBase::Windowize();
}

