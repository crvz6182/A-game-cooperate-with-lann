#pragma once
#include <string>

class String{
public:

	//���캯��

	//��ʼ��Ϊʹ���ַ����������й����String�����
	String();

	//��ʼ��Ϊʹ����L��\0����β��C�����ַ���cStr���й����String�����
	String(const wchar_t* cStr);

	//��ʼ��Ϊʹ�õ����ַ����й����String�����
	String(const wchar_t& wc);

	//��ʼ��Ϊʹ��int���ͽ��й����String�����
	String(const int& i);

	//��ʼ��Ϊʹ��float���ͽ��й����String�����
	String(const float& f);

	//�������캯��
	String(const String& s);

	//��������

	~String();

	String operator+(const String& b);
	String operator*(const int& b);
	bool operator==(const String& b);

private:

	std::wstring mContent;	//�ַ����͵ľ�������
};