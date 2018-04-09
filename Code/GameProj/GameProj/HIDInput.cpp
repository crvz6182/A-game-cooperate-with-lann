#include "stdafx.h"
#include "HIDInput.h"

HIDInput::~HIDInput()
{
	Release();
}

HIDInput * HIDInput::GetHIDInput()
{
	static HIDInput* gHIDInput = nullptr;
	if (gHIDInput == nullptr) {
		gHIDInput = new HIDInput;
	}
	return gHIDInput;
}

void HIDInput::DestroyHIDInput()
{
	HIDInput* gHIDInput = GetHIDInput();
	gHIDInput->Release();
	delete gHIDInput;
}

bool HIDInput::QueryInputs()
{
	if (!QueryDevice(mKeyboardInput, mKeyboardState, sizeof(mKeyboardState))) {
		return false;
	}
	if (!QueryDevice(mMouseInput, &mMouseState, sizeof(mMouseState))) {
		return false;
	}
	return true;
}

InputInformations HIDInput::GetBehaviours()
{
	InputInformations tReturn;
	bool moveRight = (bool)GetKeyState(DIK_D);
	if (moveRight) {
		BreakPoint();
	}
	tReturn.Append(Pair<String, Percent>("MoveRight", (Percent)moveRight));
	return tReturn;
}

char HIDInput::GetKeyState(DWORD macroKeys_DIK_)
{
	return mKeyboardState[macroKeys_DIK_] & 0x80;
}

bool HIDInput::Initialize(HINSTANCE hInstance, HWND hWindow)
{
	HR(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(&mInput), 0));

	HR(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboardInput, 0));
	HR(mInput->CreateDevice(GUID_SysMouse, &mMouseInput, 0));

	HR(mKeyboardInput->SetDataFormat(&c_dfDIKeyboard));
	HR(mKeyboardInput->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	HR(mMouseInput->SetDataFormat(&c_dfDIMouse));
	HR(mMouseInput->SetCooperativeLevel(hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	
	ZeroInitialize(mKeyboardState);
	ZeroInitialize(&mMouseState);
	return true;
}

ULONG HIDInput::Release()
{
	ReleaseCOM(mMouseInput);
	ReleaseCOM(mKeyboardInput);
	ReleaseCOM(mInput);
	return 0;
}

HIDInput::HIDInput()
{
}

bool HIDInput::QueryDevice(LPDIRECTINPUTDEVICE8 & inputDevice, LPVOID stateBuffer, DWORD bufferSize)
{
	HRESULT hResult;

	while (true) {
		hResult = inputDevice->GetDeviceState(bufferSize, stateBuffer);
		if (SUCCEEDED(hResult)) {
			break;
		}
		if (hResult != DIERR_INPUTLOST && hResult != DIERR_NOTACQUIRED) {
			return false;
		}
		if (FAILED(inputDevice->Acquire())) {
			return false;
		}
	}

	return true;
}
