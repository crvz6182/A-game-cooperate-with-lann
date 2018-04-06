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

//文件输入输出基类
class IFileIOBase {
public:

	//构造和析构
	IFileIOBase();
	~IFileIOBase();

	/*
	传入文件地址，输出该文件是否存在（若不存在则可以认为是第一次启动游戏，
	则可以例如读取玩家电脑配置进行默认设置，但是无论返回是true还是false，都必须保证此文件此时已经创建）
	*/
	bool SetFileDirectory(const String& directory);

	//返回保存的文件路径
	std::string GetFileDirectory();

	//新建路径
	int32_t createDirectory(const std::string &directoryPath);
	
private:
	
	//文件路径
	String mFileDirectory;

};

//ASCII文件输入输出层
class IAsciiFileIOLayer : public IFileIOBase {
public:

	//构造和析构
	IAsciiFileIOLayer();
	~IAsciiFileIOLayer();

	//传入属性（属性字符串的格式有待决定）输出属性值字符串
	virtual const String GetAttributeValue(const String& attribute) = 0;

	//传入目标属性，设置目标属性的值
	virtual bool SetAttributeValue(const String& attribute, const String& value) = 0;
};


class BinaryBuffer
{
public:

};

//二进制文件输入输出层
class IBinaryFileIOLayer : public IFileIOBase {
public:

	//构造和析构
	IBinaryFileIOLayer();
	~IBinaryFileIOLayer();

	virtual BinaryBuffer ReadBinary() = 0;

	virtual bool WriteBinary(const BinaryBuffer& buffer) = 0;
};

//包装实现对于Json格式文件的读写
class JsonCommunicator : public IAsciiFileIOLayer {
public:
	
	//构造和析构
	JsonCommunicator();
	~JsonCommunicator();

	//传入属性（属性字符串的格式有待决定）输出属性值字符串
	const String GetAttributeValue(const String& attribute);

	//传入目标属性，设置目标属性的值
	bool SetAttributeValue(const String& attribute, const String& value);
};

//包装实现对于二进制文件的读写
class BinaryCommunicator : public IBinaryFileIOLayer 
{
public:

};

class BinaryFormat
{
public:

};

