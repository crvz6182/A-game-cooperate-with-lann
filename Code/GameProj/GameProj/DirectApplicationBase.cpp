#include "stdafx.h"
#include "DirectApplicationBase.h"

namespace {
	DirectApplicationBase* globalDirectApplicationForTrasport = nullptr;		//���ڽ���Ա����MessageProcessת��Ϊ����ص�����
}

LRESULT CALLBACK ForwardMessageProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//ת����Ա����
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
		//�����屻������߽����ʱ��ᷢ��WM_ACTIVATE
		//�������ʱ��ͣ�����ڼ���ʱ�ָ�
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) {
			Pause();
		}
		else {
			Resume();
		}
		return 0;

		//�������С���ı�ʱ�ᷢ��WM_SIZE��Ϣ
		//�˴�ֻ���� ��� ��С�� �ָ������Ͻ�������ť��
		//���������Ե��WM_ENTERSIZEMOVE����
	case WM_SIZE:
		//����δ��ʼ��D3D����ʲôҲ����
		//���洰���С
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

		//�����ץס�����Եʱ�ᷢ��WM_ENTERSIZEMOVE��Ϣ
		//��ʱ��ͣ������
	case WM_ENTERSIZEMOVE:
		Pause();
		return 0;

		//������ɿ������Եʱ�ᷢ��WM_EXITSIZEMOVE��Ϣ
		//��ʱ�ָ������첢���ø���
	case WM_EXITSIZEMOVE:
		Resume();
		OnResize();
		return 0;

		//���ٴ���ʱ
	case WM_DESTROY:
		Quit();
		return 0;

		//TONOTE:
	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);

		//ϵͳѯ���Ƿ����ô��������С
		//�˴����ô�����СΪ800*600
		//��ֹ�����ù�С
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize = { 800, 600 };
		return 0;

		//�����Ϣת������Ա�������麯����
		//���û��Զ��帲д
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
