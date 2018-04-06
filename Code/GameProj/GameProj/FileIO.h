#pragma once
#include "stdafx.h"
#include "String.h"
#include <io.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h> 
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/writer.h"
#include "ThirdParty/rapidjson/stringbuffer.h"

//�ļ������������
class IFileIOBase {
public:

	//���������
	IFileIOBase();
	~IFileIOBase();

	/*
	�����ļ���ַ��������ļ��Ƿ���ڣ����������������Ϊ�ǵ�һ��������Ϸ��
	����������ȡ��ҵ������ý���Ĭ�����ã��������۷�����true����false�������뱣֤���ļ���ʱ�Ѿ�������
	*/
	bool SetFileDirectory(const String& directory);

	//���ر�����ļ�·��
	std::string GetFileDirectory();

	//�½�·��
	int32_t createDirectory(const std::string &directoryPath);
	
private:
	
	//�ļ�·��
	String mFileDirectory;

};

//ASCII�ļ����������
class IAsciiFileIOLayer : public IFileIOBase {
public:

	//���������
	IAsciiFileIOLayer();
	~IAsciiFileIOLayer();

	//�������ԣ������ַ����ĸ�ʽ�д��������������ֵ�ַ���
	virtual const String GetAttributeValue(const String& attribute) = 0;

	//����Ŀ�����ԣ�����Ŀ�����Ե�ֵ
	virtual bool SetAttributeValue(const String& attribute, const String& value) = 0;
};


class BinaryBuffer
{
public:

};

//�������ļ����������
class IBinaryFileIOLayer : public IFileIOBase {
public:

	//���������
	IBinaryFileIOLayer();
	~IBinaryFileIOLayer();

	virtual BinaryBuffer ReadBinary() = 0;

	virtual bool WriteBinary(const BinaryBuffer& buffer) = 0;
};

//��װʵ�ֶ���Json��ʽ�ļ��Ķ�д
class JsonCommunicator : public IAsciiFileIOLayer {
public:
	
	//���������
	JsonCommunicator();
	~JsonCommunicator();

	//�������ԣ������ַ����ĸ�ʽ�д��������������ֵ�ַ���
	const String GetAttributeValue(const String& attribute);

	//����Ŀ�����ԣ�����Ŀ�����Ե�ֵ
	bool SetAttributeValue(const String& attribute, const String& value);
};

//��װʵ�ֶ��ڶ������ļ��Ķ�д
class BinaryCommunicator : public IBinaryFileIOLayer 
{
public:

};

class BinaryFormat
{
public:

};

