#pragma once
#include <sstream>
#include <string>

using Count = unsigned int;

class String{
public:

	//���캯��

	//��ʼ��Ϊʹ���ַ����������й����String�����
	String();

	//��ʼ��Ϊʹ����'\0'��β��C�����ַ���cStr���й����String�����
	String(const char* cStr);

	//��ʼ��Ϊʹ�õ����ַ����й����String�����
	String(const char& wc);

	//��ʼ��Ϊʹ����L'\0'��β��C�����ַ���cStr���й����String�����
	String(const wchar_t* cStr);

	//��ʼ��Ϊʹ�õ������ַ����й����String�����
	String(const wchar_t& wc);

	//��ʼ��Ϊʹ��int���ͽ��й����String�����
	String(const int& i);

	//��ʼ��Ϊʹ��float���ͽ��й����String�����
	String(const float& f);

	//�������캯��
	String(const String& s);

	//��������

	~String();

	//�ַ����ϲ�
	const String operator+(const String& rhs) const;
	//�ַ����Ը���
	const String operator*(const int& rhs) const;
	//�ַ����Ƚ�
	const bool operator==(const String& rhs) const;
	//�����ַ�������
	const Count GetLength() const;

	//�ṩ��ʽ����ת��
	operator const WCHAR*() const;
	operator const std::string() const;
	operator const int() const;

private:

	std::wstring mContent;	//�ַ����͵ľ�������
};