#include "stdafx.h"
#include "String.h"
#include <sstream>


String::String() {
	content = L"";
}

String::~String() {

}

String::String(const wchar_t* cStr){
	content = cStr;
}

String::String(const wchar_t& wc) {
	wchar_t temp[2];
	temp[0] = wc;
	temp[1] = L'\0';
	content = temp;
}

String::String(const int& i) {
	std::wostringstream oss;
	oss << i;
	content = oss.str();
}

String::String(const float& f) {
	std::wostringstream oss;
	oss << f;
	content = oss.str();
}

String::String(const String& s) {
	content = s.content;
}

String String::operator+(const String& b) {
	String temp;
	temp.content = content + b.content;
	return temp;
}

String String::operator*(const int& b) {
	String temp;
	for (int i = 0; i < b; i++) {
		temp.content += content;
	}
	return temp;
}

bool String::operator==(const String& b) {
	return content.compare(b.content) == 0;
}