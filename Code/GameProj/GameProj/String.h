#pragma once
#include <sstream>
#include <string>

class String{
public:

	//构造函数

	//初始化为使用字符串””进行构造的String类对象
	String();

	//初始化为使用以'\0'结尾的C类型字符串cStr进行构造的String类对象
	String(const char* cStr);

	//初始化为使用单个字符进行构造的String类对象
	String(const char& wc);

	//初始化为使用以L'\0'结尾的C类型字符串cStr进行构造的String类对象
	String(const wchar_t* cStr);

	//初始化为使用单个长字符进行构造的String类对象
	String(const wchar_t& wc);

	//初始化为使用int类型进行构造的String类对象
	String(const int& i);

	//初始化为使用float类型进行构造的String类对象
	String(const float& f);

	//拷贝构造函数
	String(const String& s);

	//析构函数

	~String();

	//字符串合并
	String operator+(const String& rhs);
	//字符串自复制
	String operator*(const int& rhs);
	//字符串比较
	bool operator==(const String& rhs);

	//提供隐式类型转换
	operator const WCHAR*();

private:

	std::wstring mContent;	//字符类型的具体内容
};