#include "stdafx.h"
#include "String.h"
#include <sstream>


String::String() {
	mContent = L"";
}

String::String(const char * cStr)
{
	std::wostringstream tOss;
	tOss << cStr;
	mContent = tOss.str();
}

String::String(const char & c)
{
	wchar_t tStr[2];
	tStr[0] = c;
	tStr[1] = '\0';
	mContent = tStr;
}

String::~String() {

}

String::String(const wchar_t* cStr){
	mContent = cStr;
}

String::String(const wchar_t& wc) {
	wchar_t tStr[2];
	tStr[0] = wc;
	tStr[1] = L'\0';
	mContent = tStr;
}

String::String(const int& i) {
	std::wostringstream tOss;
	tOss << i;
	mContent = tOss.str();
}

String::String(const float& f) {
	std::wostringstream tOss;
	tOss << f;
	mContent = tOss.str();
}

String::String(const String& s) {
	mContent = s.mContent;
}

String String::operator+(const String& rhs) {
	String tStr;
	tStr.mContent = mContent + rhs.mContent;
	return tStr;
}

String String::operator*(const int& rhs) {
	String tStr;
	for (int i = 0; i < rhs; i++) {
		tStr.mContent += mContent;
	}
	return tStr;
}

bool String::operator==(const String& rhs) {
	return mContent.compare(rhs.mContent) == 0;
}

String::operator const WCHAR*()
{
	return mContent.c_str();
}
