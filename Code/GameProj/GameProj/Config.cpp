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
	String tValue_x;
	tValue_x = mFile.GetAttributeValue("mResolution_x");
	if (tValue_x.GetLength() == 0) {
		//无配置文件时初始化
		mResolution.Width = 1280;
		mResolution.Height = 768;
		mRefreshRate = 60;
		mAntiAliasLevel = 2;
		mIsFullScreen = true;
		mIsAntiAlias = true;
		mAntiAliasType = MSAA;
		SetConfig();
	}
	else {
		mResolution.Width = (Size1D)tValue_x;
		String tValue_y = mFile.GetAttributeValue("mResolution_y");
		mResolution.Height = (Size1D)tValue_y;
		tValue_x = mFile.GetAttributeValue("mRefreshRate");
		mRefreshRate = tValue_x;
		tValue_x = mFile.GetAttributeValue("mAntiAliasLevel");
		mAntiAliasLevel = tValue_x;
		int tValue;
		tValue = mFile.GetAttributeValue("mIsFullScreen");
		if (tValue == 0) {
			mIsFullScreen = false;
		}
		else {
			mIsFullScreen = true;
		}
		tValue = mFile.GetAttributeValue("mIsAntiAlias");
		if (tValue == 0) {
			mIsAntiAlias = false;
		}
		else {
			mIsAntiAlias = true;
		}
		tValue = mFile.GetAttributeValue("mAntiAliasType");
		if (tValue == 0) {
			mAntiAliasType = MSAA;
		}
		else {
			mAntiAliasType = FXAA;
		}
	}
}

void VideoSettingConfig::SetConfig() {
	String tValue = mResolution.Width;
	mFile.SetAttributeValue("mResolution_x", tValue);
	tValue = mResolution.Height;
	mFile.SetAttributeValue("mResolution_y", tValue);
	tValue = mRefreshRate;
	mFile.SetAttributeValue("mRefreshRate", tValue);
	tValue = mAntiAliasLevel;
	mFile.SetAttributeValue("mAntiAliasLevel", tValue);
	if (mIsFullScreen == 0)
		tValue = 0;
	else
		tValue = 1;
	mFile.SetAttributeValue("mIsFullScreen", tValue);
	if (mIsAntiAlias == 0)
		tValue = 0;
	else
		tValue = 1;
	mFile.SetAttributeValue("mIsAntiAlias", tValue);
	if (mAntiAliasType == 0)
		tValue = 0;
	else
		tValue = 1;
	mFile.SetAttributeValue("mAntiAliasType", tValue);
}

Size2D VideoSettingConfig::GetResolution() const{
	Size2D tRes;
	tRes.Height = mResolution.Width;
	tRes.Width = mResolution.Height;
	return tRes;
}

void VideoSettingConfig::SetResolution(Size2D par){
	mResolution.Width = par.Height;
	mResolution.Height = par.Width;
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

