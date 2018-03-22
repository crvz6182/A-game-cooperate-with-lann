#pragma once

#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <assert.h>
#include "String.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//释放Direct组件
#define ReleaseCOM(x) {if(x){x->Release();}x=nullptr;}

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