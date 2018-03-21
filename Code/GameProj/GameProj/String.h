#pragma once
#include <string>

class String{
public:

	//构造函数

	//初始化为使用字符串””进行构造的String类对象
	String();

	//初始化为使用以L’\0’结尾的C类型字符串cStr进行构造的String类对象
	String(const wchar_t* cStr);

	//初始化为使用单个字符进行构造的String类对象
	String(const wchar_t& wc);

	//初始化为使用int类型进行构造的String类对象
	String(const int& i);

	//初始化为使用float类型进行构造的String类对象
	String(const float& f);

	//拷贝构造函数
	String(const String& s);

	//析构函数

	~String();

	String operator+(const String& b);
	String operator*(const int& b);
	bool operator==(const String& b);

private:

	std::wstring mContent;	//字符类型的具体内容
};