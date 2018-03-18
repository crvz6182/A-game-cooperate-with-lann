#include "stdafx.h"
#include "DirectApplicationBase.h"

namespace {
	DirectApplicationBase* globalDirectApplicationForTrasport = nullptr;		//用于将成员函数MessageProcess转发为窗体回调函数
}

LRESULT CALLBACK ForwardMessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//转发成员函数
	return globalDirectApplicationForTrasport->MessageProcess(hWnd, msg, wParam, lParam);
}

DirectApplicationBase::DirectApplicationBase(HINSTANCE instance):
	mApplicationInstance(instance),
	mMainWIndowHandler(0),
	mTimer()
{
	mWindowSize.Weight = 800;
	mWindowSize.Height = 600;

	globalDirectApplicationForTrasport = this;
}

DirectApplicationBase::~DirectApplicationBase()
{
}

HINSTANCE DirectApplicationBase::GetApplicationInstance() const
{
	return mApplicationInstance;
}

HWND DirectApplicationBase::GetWindowHandler() const
{
	return mMainWIndowHandler;
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

void DirectApplicationBase::Quit()
{
	PostQuitMessage(0);
}

bool DirectApplicationBase::Initialization()
{
	return InitializeMainWindow();
}

void DirectApplicationBase::OnResize()
{
}

void DirectApplicationBase::Update(TimePointInSecond timeElapsed)
{
}

void DirectApplicationBase::Draw()
{
}

LRESULT DirectApplicationBase::MessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//当窗体被激活或者解除的时候会发出WM_ACTIVATE
		//当被解除时暂停，并在激活时恢复
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) {
			Pause();
		}
		else {
			Resume();
		}
		return 0;

		//当窗体大小被改变时会发出WM_SIZE消息
		//此处只处理 最大化 最小化 恢复（右上角三个按钮）
		//拉动窗体边缘由WM_ENTERSIZEMOVE处理
	case WM_SIZE:
		//若还未初始化D3D，则什么也不做
		//保存窗体大小
		mWindowSize.Weight = LOWORD(lParam);
		mWindowSize.Height = HIWORD(lParam);
		switch (wParam)
		{
		case SIZE_MINIMIZED:
			Minimize();
			break;
		case SIZE_MAXIMIZED:
			Maximize();
			break;
		case SIZE_RESTORED:
			Windowize();
			break;
		default:
			break;
		}
		return 0;

		//当鼠标抓住窗体边缘时会发出WM_ENTERSIZEMOVE消息
		//此时暂停并插旗
	case WM_ENTERSIZEMOVE:
		Pause();
		return 0;

		//当鼠标松开窗体边缘时会发出WM_EXITSIZEMOVE消息
		//此时恢复、拔旗并调用更新
	case WM_EXITSIZEMOVE:
		Resume();
		OnResize();
		return 0;

		//销毁窗体时
	case WM_DESTROY:
		Quit();
		return 0;

		//TONOTE:
	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);

		//系统询问是否设置窗体最大最小
		//此处设置窗体最小为800*600
		//防止窗体变得过小
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize = { 800, 600 };
		return 0;

		//鼠标消息转发到成员函数（虚函数）
		//供用户自定义覆写
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		//OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_MOUSEMOVE:
		//OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool DirectApplicationBase::InitializeMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ForwardMessageProcess;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mApplicationInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"D3DApp";

	if (!RegisterClass(&wc)) {
		/*DWORD e = GetLastError();
		std::wstringstream wss;
		wss << L"Register Class Failed.\nFail Error Code: " << e;
		wstring err = wss.str();
		MessageBox(0, err.c_str(), 0, 0);*/
		return false;
	}

	RECT rect = { 0, 0, mWindowSize.Weight, mWindowSize.Height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	mMainWIndowHandler = CreateWindow(L"D3DApp", /*mCaption.c_str()*/L"DirectApplication",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		mWindowSize.Weight, mWindowSize.Height, 0, 0, mApplicationInstance, 0);

	if (!mMainWIndowHandler) {
		/*DWORD e = GetLastError();
		std::wstringstream wss;
		wss << L"Create Window Failed.\nFail Error Code: " << e;
		wstring err = wss.str();
		MessageBox(0, err.c_str(), 0, 0);*/
		return false;
	}

	ShowWindow(mMainWIndowHandler, SW_SHOW);
	UpdateWindow(mMainWIndowHandler);

	return true;
}

void DirectApplicationBase::Pause()
{
	mTimer.PauseTimer();
}

void DirectApplicationBase::Resume()
{
	mTimer.ResumeTime();
}

void DirectApplicationBase::Windowize()
{
}

void DirectApplicationBase::Minimize()
{
}

void DirectApplicationBase::Maximize()
{
}
