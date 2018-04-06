#include "stdafx.h"
#include "String.h"



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

const String String::operator+(const String& rhs) const
{
	String tStr;
	tStr.mContent = mContent + rhs.mContent;
	return tStr;
}

const String String::operator*(const int& rhs) const
{
	String tStr;
	for (int i = 0; i < rhs; i++) {
		tStr.mContent += mContent;
	}
	return tStr;
}

const bool String::operator==(const String& rhs) const
{
	return mContent.compare(rhs.mContent) == 0;
}

const Count String::GetLength() const
{
	return mContent.length();
}

String::operator const WCHAR* ()const
{
	return mContent.c_str();
}

String::operator const std::string ()const
{
	if (mContent.length() == 0)
		return "";

	std::string str;
	str.assign(mContent.begin(), mContent.end());
	return str;
}

String::operator const int()const
{
	return std::stoi(mContent);
}

String::operator const float()const
{
	return std::stof(mContent);
}
