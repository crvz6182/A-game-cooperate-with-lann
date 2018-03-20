#pragma once
#include <string>

class String
{
public:

	String();
	String(const wchar_t* cStr);
	String(const wchar_t& wc);
	String(const int& i);
	String(const float& f);
	String(const String& s);
	~String();

	String operator+(const String& b);
	String operator*(const int& b);
	bool operator==(const String& b);

private:

	std::wstring content;
};