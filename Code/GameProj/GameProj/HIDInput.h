#pragma once
#include "DirectUtility.h"

typedef char KeyboardState[256];

//人体工程学设备输入类
class HIDInput
{
public:
	~HIDInput();

	//获取单例
	static HIDInput* GetHIDInput();
	//销毁单例
	static void DestroyHIDInput();

	//询问当前所有输入
	bool QueryInputs();

	//获取当前键盘按键状态
	char GetKeyState(DWORD macroKeys_DIK_);

	//初始化
	bool Initialize(HINSTANCE hInstance, HWND hWindow);
	
	//释放
	ULONG Release();
private:
	HIDInput();

	//获取指定设备的输入到指定大小的指定缓冲区
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);
private:
	IDirectInput8*							mInput;							//D3D输入层
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//键盘输入
	LPDIRECTINPUTDEVICE8			mMouseInput;					//鼠标输入

	DIMOUSESTATE						mMouseState;					//鼠标状态
	KeyboardState							mKeyboardState;				//键盘状态
};