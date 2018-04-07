#include "stdafx.h"
#include "Config.h"

Config::Config(const String &fileName) {

}

Config::~Config() {

}

VideoSettingConfig::VideoSettingConfig(const String &fileName) :Config(fileName) {
	mFile.SetFileDirectory(fileName);
}

VideoSettingConfig::~VideoSettingConfig() {

}

void VideoSettingConfig::GetConfig() {
	bool tIsConfigComplete = true;
	String tValue_x;
	String tValue_y;
	int tValue;
	tValue_x = mFile.GetAttributeValue("Resolution_x");
	if (tValue_x == "" || tValue_x.toInt() <= 0)
		tIsConfigComplete = false;
	tValue_y = mFile.GetAttributeValue("Resolution_y");
	if (tValue_y == "" || tValue_y.toInt() <= 0)
		tIsConfigComplete = false;
	tValue_x = mFile.GetAttributeValue("RefreshRate");
	if (tValue_x == "" || tValue_x.toInt() <= 0)
		tIsConfigComplete = false;
	tValue_x = mFile.GetAttributeValue("AntiAliasLevel");
	if (tValue_x == "" || (tValue_x.toInt() != 2 && tValue_x.toInt() != 4 && tValue_x.toInt() != 8))
		tIsConfigComplete = false;
	tValue_x = mFile.GetAttributeValue("IsFullScreen");
	if (tValue_x == "" || !(tValue_x == "0" || tValue_x == "1"))
		tIsConfigComplete = false;
	tValue_x = mFile.GetAttributeValue("IsAntiAlias");
	if (tValue_x == "" || !(tValue_x == "0" || tValue_x == "1"))
		tIsConfigComplete = false;
	tValue_x = mFile.GetAttributeValue("AntiAliasType");
	if (tValue_x == "" || !(tValue_x == "0" || tValue_x == "1"))
		tIsConfigComplete = false;
	if (tIsConfigComplete) {
		tValue_x = mFile.GetAttributeValue("Resolution_x");
		mResolution.Width = (Size1D)tValue_x.toInt();
		tValue_y = mFile.GetAttributeValue("Resolution_y");
		mResolution.Height = (Size1D)tValue_y.toInt();
		tValue_x = mFile.GetAttributeValue("RefreshRate");
		mRefreshRate = tValue_x.toInt();
		tValue_x = mFile.GetAttributeValue("AntiAliasLevel");
		mAntiAliasLevel = tValue_x.toInt();
		tValue = mFile.GetAttributeValue("IsFullScreen").toInt();
		mIsFullScreen = tValue;
		tValue = mFile.GetAttributeValue("IsAntiAlias").toInt();
		mIsAntiAlias = tValue;
		tValue = mFile.GetAttributeValue("AntiAliasType").toInt();
		mAntiAliasType = (AntiAliasType)tValue;
	}
	else {
		//配置文件不正确时初始化
		mResolution.Width = 1920;
		mResolution.Height = 1080;
		mRefreshRate = 60;
		mAntiAliasLevel = 4;
		mIsFullScreen = true;
		mIsAntiAlias = true;
		mAntiAliasType = MSAA;
		SetConfig();
	}
}

void VideoSettingConfig::SetConfig() {
	String tValue = mResolution.Width;
	mFile.SetAttributeValue("Resolution_x", tValue);
	tValue = mResolution.Height;
	mFile.SetAttributeValue("Resolution_y", tValue);
	tValue = mRefreshRate;
	mFile.SetAttributeValue("RefreshRate", tValue);
	tValue = mAntiAliasLevel;
	mFile.SetAttributeValue("AntiAliasLevel", tValue);
	if (mIsFullScreen)
		tValue = "1";
	else
		tValue = "0";
	mFile.SetAttributeValue("IsFullScreen", tValue);
	if (mIsAntiAlias)
		tValue = "1";
	else
		tValue = "0";
	mFile.SetAttributeValue("IsAntiAlias", tValue);
	tValue = mAntiAliasType;
	mFile.SetAttributeValue("AntiAliasType", tValue);
}

Size2D VideoSettingConfig::GetResolution() const{
	return mResolution;
}

void VideoSettingConfig::SetResolution(Size2D par){
	mResolution = par;
}

int VideoSettingConfig::GetRefreshRate() const{
	return mRefreshRate;
}

void VideoSettingConfig::SetRefreshRate(int par){
	mRefreshRate = par;
}

int VideoSettingConfig::GetAntiAliasLevel() const{
	return mAntiAliasLevel;
}

void VideoSettingConfig::SetAntiAliasLevel(int par){
	mAntiAliasLevel = par;
}

bool VideoSettingConfig::GetIsFullScreen() const{
	return mIsFullScreen;
}

void VideoSettingConfig::SetIsFullScreen(bool par){
	mIsFullScreen = par;
}

bool VideoSettingConfig::GetIsAntiAlias() const{
	return mIsAntiAlias;
}

void VideoSettingConfig::SetIsAntiAlias(bool par){
	mIsAntiAlias = par;
}

AntiAliasType VideoSettingConfig::GetAntiAliasType() const{
	return mAntiAliasType;
}

void VideoSettingConfig::SetAntiAliasType(AntiAliasType par){
	mAntiAliasType = par;
}

Array<Size2D> VideoSettingConfig::GetAllResolutions() const {
	static Array<Size2D> list = {
		{640, 480},
		{800, 600},
		{1024, 768},
		{1152, 864},
		{1280, 600},
		{1280, 720},
		{1280, 768},
		{1280, 800},
		{1280, 960},
		{1280, 1024},
		{1360, 768},
		{1366, 768},
		{1400, 900},
		{1400, 1050},
		{1600, 900},
		{1680, 1050},
		{1920, 1080}
	};
	return list;
}

Array<AntiAliasType> VideoSettingConfig::GetAllAntiAliasType() const {
	static Array<AntiAliasType> list{
		MSAA,
		FXAA
	};
	return list;
}

Array<int> VideoSettingConfig::GetAllAntiAliasLevel() const {
	static Array<int> list{
		2,
		4,
		8
	};
	return list;
}

