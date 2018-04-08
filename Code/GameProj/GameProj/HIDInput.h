#pragma once
#include "DirectUtility.h"
#include "Actor.h"

constexpr UINT KEYBOARD_SIZE = 256;

//动作行为状态
enum ActionState
{
	Idle = 0,				//00
	Press = 1,				//01
	Release = 2,			//10
	Hold = 3,				//11
	ACTION_SIZE
};

using KeyboardState = ArrayFixed<char, KEYBOARD_SIZE>;
using KeyboardAction = ArrayFixed<ActionState, KEYBOARD_SIZE>;

using KeyToBehavior = ArrayFixed<String, KEYBOARD_SIZE>;		//按键映射到字符串
using InputInformations = Array<Pair<String, Percent>>;		//输入信息


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
	bool GetKeyState(DWORD macroKeys_DIK_);

	//初始化
	bool Initialize(HINSTANCE hInstance, HWND hWindow);

	//释放
	ULONG Release();
private:
	HIDInput();

	//获取指定设备的输入到指定大小的指定缓冲区
	bool QueryDevice(LPDIRECTINPUTDEVICE8& inputDevice, LPVOID stateBuffer, DWORD bufferSize);

	void BindKey(DWORD macroKey_DIK_, const String& str);
private:
	IDirectInput8*							mInput;							//D3D输入层
	LPDIRECTINPUTDEVICE8			mKeyboardInput;			//键盘输入
	LPDIRECTINPUTDEVICE8			mMouseInput;					//鼠标输入

	DIMOUSESTATE						mMouseState;					//鼠标状态
	KeyboardState							mKeyboardState;				//键盘本次状态
	KeyboardState							mPreviousState;				//键盘上次状态
	KeyboardAction						mKeyboardAction;			//键盘行为

	KeyToBehavior						mKeyMap;						//按键映射到动作字符串

	InputInformations					mInformations;				//用户输入信息
};