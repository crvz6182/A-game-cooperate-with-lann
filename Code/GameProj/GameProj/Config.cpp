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
	String tValue;
	tValue = mFile.GetAttributeValue("Resolution_x");
	if(IsPositive(tValue))
		mResolution.Width = (Size1D)tValue.toInt();
	else
		mResolution.Width = 1920;
	tValue = mFile.GetAttributeValue("Resolution_y");
	if (IsPositive(tValue))
		mResolution.Height = (Size1D)tValue.toInt();
	else
		mResolution.Height = 1080;
	tValue = mFile.GetAttributeValue("RefreshRate");
	if (IsPositive(tValue))
		mRefreshRate = tValue.toInt();
	else
		mRefreshRate = 60;
	tValue = mFile.GetAttributeValue("AntiAliasLevel");
	if (IsAntiAliasLevel(tValue))
		mAntiAliasLevel = tValue.toInt();
	else
		mAntiAliasLevel = 4;
	tValue = mFile.GetAttributeValue("IsFullScreen");
	if (IsBool(tValue))
		mIsFullScreen = tValue.toInt();
	else
		mIsFullScreen = true;
	tValue = mFile.GetAttributeValue("IsAntiAlias");
	if (IsBool(tValue))
		mIsAntiAlias = tValue.toInt();
	else
		mIsAntiAlias = true;
	tValue = mFile.GetAttributeValue("AntiAliasType");
	if (IsBool(tValue))
		mAntiAliasType = (AntiAliasType)tValue.toInt();
	else
		mAntiAliasType = MSAA;
	SetConfig();
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

bool VideoSettingConfig::IsPositive(String value) const {
	return !(value == "" || value.toInt() <= 0);
}

bool VideoSettingConfig::IsBool(String value) const {
	return !(value == "" || !(value == "0" || value == "1"));
}

bool VideoSettingConfig::IsAntiAliasLevel(String value) const {
	return !(value == "" || (value.toInt() != 2 && value.toInt() != 4 && value.toInt() != 8));
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

