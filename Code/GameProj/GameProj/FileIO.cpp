#include "stdafx.h"
#include "FileIO.h"

using namespace rapidjson;

IFileIOBase::IFileIOBase() {

}

IFileIOBase::~IFileIOBase() {

}

bool IFileIOBase::SetFileDirectory(const String& directory) {
	const wchar_t *tLDir = directory;
	std::fstream tIn;
	tIn.open(tLDir);
	mFileDirectory = directory;
	if (!tIn) {
		std::ofstream tOut(tLDir);
		if (tOut) { // 如果创建成功
			tOut.close();  // 执行完操作后关闭文件句柄
		}
		else {
			//创建失败
		}
		return false;
	}
	else {
		return true;
	}
}

String IFileIOBase::GetFileDirectory() {
	return mFileDirectory;
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
	std::filebuf *tPbuf;
	std::ifstream tFilestr;
	long long tSize;
	char *tBuffer;
	const wchar_t *tLDir = this->GetFileDirectory();
	const std::string tAttribute = attribute;
	tFilestr.open(tLDir);
	tPbuf = tFilestr.rdbuf();
	tSize = tPbuf->pubseekoff(0, std::ios::end, std::ios::in);
	if (tSize != -1) {
		tPbuf->pubseekpos(0, std::ios::in);
		tBuffer = new char[static_cast <unsigned int>(tSize)];
		tPbuf->sgetn(tBuffer, tSize);
		tFilestr.close();
		Document tDocument;
		const char *tCBuffer = tBuffer;
		tDocument.Parse(tCBuffer);
		return tDocument[tAttribute.c_str()].GetString();
	}
	else {
		return "";
	}
}

bool JsonCommunicator::SetAttributeValue(const String& attribute, const String& value) {
	std::filebuf *tPbuf;
	std::fstream tFile;
	std::ifstream tFilestr;
	std::ofstream tFileout;
	long long tSize;
	char *tBuffer;
	const wchar_t *tLDir = this->GetFileDirectory();
	const std::string tAttribute = attribute;
	const std::string tValue = value;
	Document tDocument;
	bool tResult;
	tFile.open(tLDir);
	if (tFile) {
		tFile.close();
		tFilestr.open(tLDir);
		tPbuf = tFilestr.rdbuf();
		tSize = tPbuf->pubseekoff(0, std::ios::end, std::ios::in);
		tPbuf->pubseekpos(0, std::ios::in);
		tBuffer = new char[static_cast <unsigned int>(tSize)];
		tPbuf->sgetn(tBuffer, tSize);
		tFilestr.close();
		const char *tCBuffer = tBuffer;
		tDocument.Parse(tCBuffer);
		if (tDocument.HasMember(tAttribute.c_str())) {
			tResult = true;
		}
		else {
			tResult = false;
		}
	}
	else {
		tFile.close();
		tResult = false;
		tDocument.SetObject();
	}
	tFileout.open(tLDir, std::ios::trunc);
	Document::AllocatorType &tAllocator = tDocument.GetAllocator();
	tDocument.RemoveMember(tAttribute.c_str());
	tDocument.AddMember(Value(tAttribute.c_str(), tAllocator), Value(tValue.c_str(), tAllocator), tAllocator);
	StringBuffer tBuf;
	PrettyWriter<StringBuffer> tPretty_writer(tBuf);
	tDocument.Accept(tPretty_writer);
	tFileout << tBuf.GetString();
	tFileout.close();
	return tResult;
}
