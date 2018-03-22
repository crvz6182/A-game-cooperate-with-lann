#include "stdafx.h"
#include "DirectUtility.h"

void TraceError(const char * fileName, DWORD lineNumber, HRESULT hr, const wchar_t * functionName)
{
	MessageBox(0, String(L"�ļ�����") + String(fileName) + String(L"\n�кţ�") + String((int)lineNumber) + String(L"\n�����룺") + String(hr) + String(L"\n������") + String(functionName), String(L"����"), 0);
}
