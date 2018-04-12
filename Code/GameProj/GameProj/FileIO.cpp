#include "stdafx.h"
#include "FileIO.h"
#define MAX_PATH_LEN 256

using namespace rapidjson;

IFileIOBase::IFileIOBase() {

}

IFileIOBase::~IFileIOBase() {

}

int32_t IFileIOBase::NewDirectory(const std::string &directoryPath)	//从网上抄的
{
	uint32_t dirPathLen = directoryPath.length();
	if (dirPathLen > MAX_PATH_LEN)
	{
		return -1;
	}
	char tmpDirPath[MAX_PATH_LEN] = { 0 };
	for (uint32_t i = 0; i < dirPathLen; ++i)
	{
		tmpDirPath[i] = directoryPath[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (_access(tmpDirPath, 0) != 0)
			{
				int32_t ret = _mkdir(tmpDirPath);
				if (ret != 0)
				{
					return ret;
				}
			}
		}
	}
	return 0;
}

bool IFileIOBase::NewFile(const std::string &tDir) {
	std::ofstream tOut;
	tOut.open(tDir, std::ios::app);
	if (tOut) { // 如果创建成功
		tOut.close();  // 关闭文件
		return true;
	}
	else {
		if (NewDirectory(tDir) != 0)
			return false;
		tOut.open(tDir, std::ios::app);
		if (tOut) { // 如果创建成功
			tOut.close();  // 关闭文件
			return true;
		}
		else {
			return false;	//创建失败
		}
	}
}

bool IFileIOBase::SetFileDirectory(const String& directory) {
	std::string tDir = directory;
	std::ifstream tIn;
	tIn.open(tDir);
	mFileDirectory = directory;
	if (!tIn) {
		return NewFile(tDir);
	}
	else {
		return true;
	}
}

std::string IFileIOBase::GetFileDirectory() {
	std::string tFileDirectory = mFileDirectory;
	return tFileDirectory;
}

IAsciiFileIOLayer::IAsciiFileIOLayer() {

}

IAsciiFileIOLayer::~IAsciiFileIOLayer() {

}

IBinaryFileIOLayer::IBinaryFileIOLayer() {

}

IBinaryFileIOLayer::~IBinaryFileIOLayer() {

}

JsonCommunicator::JsonCommunicator() {

}

JsonCommunicator::~JsonCommunicator() {

}

const String JsonCommunicator::GetAttributeValue(const String& attribute) {
	std::stringstream tPbuf;
	std::ifstream tFilestr;
	std::string tDir = GetFileDirectory();
	const std::string tAttribute = attribute;
	tFilestr.open(tDir);
	tPbuf << tFilestr.rdbuf();
	if (tPbuf.str().length() > 0) {
		Document tDocument;
		std::string tBuffer(tPbuf.str());
		tDocument.Parse<0>(tBuffer.c_str());
		if (tDocument.HasParseError())
			return "";
		if (!tDocument.HasMember(tAttribute.c_str()))
			return "";
		return tDocument[tAttribute.c_str()].GetString();
	}
	else {
		tFilestr.close();
		return "";
	}
}

bool JsonCommunicator::SetAttributeValue(const String& attribute, const String& value) {
	std::stringstream tPbuf;
	std::fstream tFile;
	std::ifstream tFilestr;
	std::ofstream tFileout;
	std::string tDir = GetFileDirectory();
	const std::string tAttribute = attribute;
	const std::string tValue = value;
	Document tDocument;
	tFile.open(tDir);
	if (tFile) {
		tFile.close();
		tFilestr.open(tDir);
		tPbuf << tFilestr.rdbuf();
		std::string tBuffer(tPbuf.str());
		if (tBuffer.length() == 0)
			tDocument.SetObject();
		else {
			tDocument.Parse<0>(tBuffer.c_str());
			if (tDocument.HasParseError()) {
				return false;
			}
		}
	}
	else {
		tDocument.SetObject();
		tFile.close();
	}
	tFileout.open(tDir, std::ios::trunc);
	Document::AllocatorType &tAllocator = tDocument.GetAllocator();
	if (tDocument.HasMember(tAttribute.c_str()))
		tDocument.RemoveMember(tAttribute.c_str());
	tDocument.AddMember(Value(tAttribute.c_str(), tAllocator), Value(tValue.c_str(), tAllocator), tAllocator);
	StringBuffer tBuf;
	PrettyWriter<StringBuffer> tPretty_writer(tBuf);
	tDocument.Accept(tPretty_writer);
	tFileout << tBuf.GetString();
	tFileout.close();
	return true;
}
