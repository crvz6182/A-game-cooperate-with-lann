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
		mResolution[0] = 1280;
		mResolution[0] = 768;
		mRefreshRate = 60;
		mAntiAliasLevel = 2;
		mIsFullScreen = True_F;
		mIsAntiAlias = True_A;
		mAntiAliasType = MSAA;
	}
	else {
		mResolution[0] = tValue_x;
		String tValue_y = mFile.GetAttributeValue("mResolution_y");
		mResolution[1] = tValue_y;
		tValue_x = mFile.GetAttributeValue("mRefreshRate");
		mRefreshRate = tValue_x;
		tValue_x = mFile.GetAttributeValue("mAntiAliasLevel");
		mAntiAliasLevel = tValue_x;
		int tValue;
		tValue = mFile.GetAttributeValue("mIsFullScreen");
		if (tValue == 0) {
			mIsFullScreen = False_F;
		}
		else {
			mIsFullScreen = True_F;
		}
		tValue = mFile.GetAttributeValue("mIsAntiAlias");
		if (tValue == 0) {
			mIsAntiAlias = False_A;
		}
		else {
			mIsAntiAlias = True_A;
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
	String tValue = mResolution[0];
	mFile.SetAttributeValue("mResolution_x", tValue);
	tValue = mResolution[1];
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
	tRes.Height = mResolution[0];
	tRes.Width = mResolution[2];
	return tRes;
}

void VideoSettingConfig::SetResolution(Size2D par){
	mResolution[0] = par.Height;
	mResolution[1] = par.Width;
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

FullScreenSetting VideoSettingConfig::GetIsFullScreen() const{
	return mIsFullScreen;
}

void VideoSettingConfig::SetIsFullScreen(FullScreenSetting par){
	mIsFullScreen = par;
}

AntiAliasSetting VideoSettingConfig::GetIsAntiAlias() const{
	return mIsAntiAlias;
}

void VideoSettingConfig::SetIsAntiAlias(AntiAliasSetting par){
	mIsAntiAlias = par;
}

AntiAliasType VideoSettingConfig::GetAntiAliasType() const{
	return mAntiAliasType;
}

void VideoSettingConfig::SetAntiAliasType(AntiAliasType par){
	mAntiAliasType = par;
}

Array<Size2D> VideoSettingConfig::GetAllResolutions() const {
	Array<Size2D> list;
	Size2D tResolution;
	tResolution.Width = 640;
	tResolution.Height = 480;
	list.push(tResolution);
	tResolution.Width = 800;
	tResolution.Height = 600;
	list.push(tResolution);
	tResolution.Width = 1024;
	tResolution.Height = 768;
	list.push(tResolution);
	tResolution.Width = 1152;
	tResolution.Height = 864;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 600;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 720;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 768;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 800;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 960;
	list.push(tResolution);
	tResolution.Width = 1280;
	tResolution.Height = 1024;
	list.push(tResolution);
	tResolution.Width = 1360;
	tResolution.Height = 768;
	list.push(tResolution);
	tResolution.Width = 1366;
	tResolution.Height = 768;
	list.push(tResolution);
	tResolution.Width = 1400;
	tResolution.Height = 900;
	list.push(tResolution);
	tResolution.Width = 1400;
	tResolution.Height = 1050;
	list.push(tResolution);
	tResolution.Width = 1600;
	tResolution.Height = 900;
	list.push(tResolution);
	tResolution.Width = 1680;
	tResolution.Height = 1050;
	list.push(tResolution);
	tResolution.Width = 1920;
	tResolution.Height = 1080;
	list.push(tResolution);
	return list;
}

Array<AntiAliasType> VideoSettingConfig::GetAllAntiAliasType() const {
	Array<AntiAliasType> list;
	list.push(MSAA);
	list.push(FXAA);
	return list;
}

Array<int> VideoSettingConfig::GetAllAntiAliasLevel() const {
	Array<int> list;
	list.push(2);
	list.push(4);
	list.push(8);
	return list;
}

