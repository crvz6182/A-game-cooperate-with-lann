#pragma once
#include "DirectUtility.h"
#include "Actor.h"

typedef char KeyboardState[256];										//键盘状态
using KeyToBehavior = Dictionary<DWORD, String>;		//按键映射到字符串
using InputInformations = Array<Pair<String, Percent>>;		//输入信息

//动作行为状态
enum ActionState
{
	Pressed = 0,
	Released = 1
};

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

	InputInformations GetBehaviours();

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

	KeyToBehavior						mKeyMap;						//按键映射到动作字符串
};