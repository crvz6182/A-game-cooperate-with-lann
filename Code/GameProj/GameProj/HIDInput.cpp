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

bool HIDInput::QueryInputsThenCallBack()
{
	if (!QueryDevice(mKeyboardInput, mKeyboardState.GetPointer(), sizeof(mKeyboardState))) {
		return false;
	}
	if (!QueryDevice(mMouseInput, &mMouseState, sizeof(mMouseState))) {
		return false;
	}

	KeyboardCallBack();

	return true;
}

bool HIDInput::GetKeyState(DWORD macroKeys_DIK_)
{
	return (mKeyboardState[macroKeys_DIK_] & 0x80) >> 7;
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
	ZeroInitialize(mKeyboardPreviousState);
	ZeroInitialize(mMouseState);

	//×Ô¶¨Òå
	BindKey(DIK_D, "MoveRight");
	BindKey(DIK_A, "MoveLeft");
	BindKey(DIK_W, "MoveUp");
	BindKey(DIK_S, "MoveDown");

	return true;
}

void HIDInput::BindActionBehaviour(const String & str, ActionState actionState, std::function<void()> func)
{
	mActionMap.Create({ str, actionState }, func);
}

ULONG HIDInput::Release()
{
	ReleaseCOM(mMouseInput);
	ReleaseCOM(mKeyboardInput);
	ReleaseCOM(mInput);
	return 0;
}

HIDInput::HIDInput() : 
	mInput(nullptr),
	mKeyboardInput(nullptr),
	mMouseInput(nullptr)
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

void HIDInput::BindKey(DWORD macroKey_DIK_, const String & str)
{
	mKeyMap[macroKey_DIK_] = str;
}

void HIDInput::KeyboardCallBack()
{
	for (Index i = 0; i < KEYBOARD_SIZE; ++i) {
		mKeyboardAction[i] = (ActionState)(((mKeyboardPreviousState[i] != 0) << 1) | (mKeyboardState[i] != 0));
		if (mKeyMap[i] == "") {
			continue;
		}
		auto callbackFunction = mActionMap.Get({ mKeyMap[i], mKeyboardAction[i] });
		if (callbackFunction != nullptr) {
			(*callbackFunction)();
		}
	}
	mKeyboardPreviousState = mKeyboardState;
}
