#pragma once
#include <sstream>
#include <string>

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
	String operator+(const String& rhs);
	//�ַ����Ը���
	String operator*(const int& rhs);
	//�ַ����Ƚ�
	bool operator==(const String& rhs);

	//�ṩ��ʽ����ת��
	operator const WCHAR*();

private:

	std::wstring mContent;	//�ַ����͵ľ�������
};