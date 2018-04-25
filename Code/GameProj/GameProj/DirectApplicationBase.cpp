#include "stdafx.h"
#include "DirectApplicationBase.h"


DirectApplicationBase::DirectApplicationBase(HINSTANCE hInstance):
	WindowApplicationBase(hInstance),
	mTimer(),
	mDevice(nullptr),
	mImmediateContext(nullptr),
	mSwapChain(nullptr),
	mMsaaQualityLevels(0),
	mRenderTargetView(nullptr),
	mDepthStencilView(nullptr),
	mDepthStencilBuffer(nullptr),
	mVideoSettingConfig("Resource\\Config\\VideoSettings.json")
{
}


DirectApplicationBase::~DirectApplicationBase()
{
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSwapChain);

	ReleaseCOM(mDepthStencilBuffer);


	//��λ����Ĭ������
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
			Draw();
		}
	}
	return (int)msg.wParam;
}

void DirectApplicationBase::OnResize()
{
	assert(mImmediateContext);
	assert(mDevice);
	assert(mSwapChain);

	//�ͷų�Ա�������еľ���ͼ�ͻ�����
	//���µĴ��������´���

	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mDepthStencilBuffer);

	//����������Ⱦ������ͼ

	HR(mSwapChain->ResizeBuffers(1, (UINT)mVideoSettingConfig.GetResolution().Width, (UINT)mVideoSettingConfig.GetResolution().Height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
	ID3D11Texture2D* backBuffer;
	HR(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(mDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
	ReleaseCOM(backBuffer);


	//ȷ��MSAA�����ȼ�����
	QueryMsaaQualityLevel();

	//�����µ����ģ����ͼ�����ģ�建����
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

	HR(mDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(mDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));

	//���½��µ���Ⱦ������ͼ�����ģ����ͼ�󶨵���ˮ��
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//�����趨�����Ӵ�

	D3D11_VIEWPORT screenViewPort;
	screenViewPort.TopLeftX = 0;
	screenViewPort.TopLeftY = 0;
	screenViewPort.Width = static_cast<float>(mWindowSize.Width);
	screenViewPort.Height = static_cast<float>(mWindowSize.Height);
	screenViewPort.MinDepth = 0.0f;
	screenViewPort.MaxDepth = 1.0f;

	mImmediateContext->RSSetViewports(1, &screenViewPort);
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
	//�����ڵ���ģʽ�£����Ե���ģʽ�����豸
#if defined(DEBUG) || defined (_DEBUG)
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//�����豸�������feature level
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

	//ȷ��MSAA�����ȼ�����
	QueryMsaaQualityLevel();

	//��������������Ĳ�������
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

	//����ʹ�� ������������ǰ�豸 �Ĺ��� ��������ƥ��Ľ�����
	//�����豸�뽻������ƥ��
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

	DirectApplicationBase::OnResize();

	return true;
}

void DirectApplicationBase::QueryMsaaQualityLevel()
{
	//ֻ��Ҫ��ѯһ��MSAA�����ȼ�
	if (mMsaaQualityLevels != 0) {
		return;
	}

	//���4xMSAA֧�ֵ������ȼ�
	//ֻҪ��֧��D3D11���豸һ��֧��4xMSAA��
	//���ֻ��Ҫ���֧�ֵ������ȼ�����
	HR(mDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, mVideoSettingConfig.GetAntiAliasLevel(), &mMsaaQualityLevels));
	assert(mMsaaQualityLevels > 0);
}

void DirectApplicationBase::Windowize()
{
	if (!mDevice) {
		return;
	}
	WindowApplicationBase::Windowize();
}

