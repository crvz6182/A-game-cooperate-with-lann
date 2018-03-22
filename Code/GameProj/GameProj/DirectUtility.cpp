#include "stdafx.h"
#include "DirectUtility.h"

void TraceError(const char * fileName, DWORD lineNumber, HRESULT hr, const wchar_t * functionName)
{
	MessageBox(0, String(L"文件名：") + String(fileName) + String(L"\n行号：") + String((int)lineNumber) + String(L"\n返回码：") + String(hr) + String(L"\n函数：") + String(functionName), String(L"错误！"), 0);
}
