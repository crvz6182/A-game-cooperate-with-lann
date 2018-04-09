#pragma once

#define INITGUID

#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dinput.h>
#include <assert.h>
#include "Math.h"
#include "String.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//释放Direct组件
#define ReleaseCOM(x) {if(x){x->Release();}x=nullptr;}
//以全零初始化
#define ZeroInitialize(x) {ZeroMemory(x, sizeof(x));}

//用于检测函数执行结果
#ifndef HR
#define HR(x)																		\
	{																						\
		HRESULT hr = (x);														\
		if(FAILED(hr))																\
		{																					\
			TraceError( __FILE__, (DWORD)__LINE__, hr, L#x);	\
		}																					\
	}
#endif

void TraceError(const char* fileName, DWORD lineNumber, HRESULT hr, const wchar_t* functionName);