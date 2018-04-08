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
	if (!QueryDevice(mKeyboardInput, mKeyboardState.GetPointer(), sizeof(mKeyboardState))) {
		return false;
	}
	if (!QueryDevice(mMouseInput, &mMouseState, sizeof(mMouseState))) {
		return false;
	}
	return true;
}

InputInformations HIDInput::GetBehaviours()
{
	mInformations.Clear();
	for (DWORD i = 0; i < KEYBOARD_SIZE; ++i) {
		mKeyboardAction[i] = (ActionState)(((mPreviousState[i] & 0x80) >> 7) | ((mKeyboardState[i] & 0x80) >> 6));

		String tActionName = mKeyMap[i];
		if (tActionName != String(L"")) {
			if (mKeyboardAction[i] != ActionState::Idle && mKeyboardAction[i] != ActionState::Hold) {
				mInformations.Append({ tActionName, (Percent)mKeyboardAction[i] });
			}
		}
	}

	mPreviousState = mKeyboardState;
	return mInformations;
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
	ZeroInitialize(mPreviousState);
	ZeroInitialize(mMouseState);

	//×Ô¶¨Òå
	BindKey(DIK_D, "MoveRight");
	BindKey(DIK_A, "MoveLeft");
	BindKey(DIK_W, "MoveUp");
	BindKey(DIK_S, "MoveDown");

	return true;
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
