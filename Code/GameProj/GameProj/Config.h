#pragma once
#include "stdafx.h"
#include "String.h"
#include "Math.h"
#include "FileIO.h"
#include <string>

enum FullScreenSetting {
	False_F = 0,
	True_F = 1
};

enum AntiAliasSetting {
	False_A = 0,
	True_A = 1
};

enum AntiAliasType {
	MSAA = 0,
	FXAA = 1
};

class Config {
public:
	Config(const String &fileName);
	~Config();
	virtual void SetConfig() = 0;
	virtual void GetConfig() = 0;

//private:

};

class VideoSettingConfig :public Config {
public:
	VideoSettingConfig(const String &fileName);
	~VideoSettingConfig();


	//读取和保存设置
	virtual void GetConfig() override;
	virtual void SetConfig() override;

	//获得和修改各项设置的临时值
	Size2D GetResolution() const;
	void SetResolution(Size2D par);
	int GetRefreshRate() const;
	void SetRefreshRate(int par);
	int GetAntiAliasLevel() const;
	void SetAntiAliasLevel(int par);
	FullScreenSetting GetIsFullScreen() const;
	void SetIsFullScreen(FullScreenSetting par);
	AntiAliasSetting GetIsAntiAlias() const;
	void SetIsAntiAlias(AntiAliasSetting par);
	AntiAliasType GetAntiAliasType() const;
	void SetAntiAliasType(AntiAliasType par);

	//获得部分设置的所有可选项
	Array<Size2D> GetAllResolutions() const;
	Array<AntiAliasType> GetAllAntiAliasType() const;
	Array<int> GetAllAntiAliasLevel() const;

private:
	//设置的临时值
	int mResolution[2];
	int mRefreshRate;
	int mAntiAliasLevel;
	FullScreenSetting mIsFullScreen;
	AntiAliasSetting mIsAntiAlias;
	AntiAliasType mAntiAliasType;

	//JSON读写类
	JsonCommunicator mFile;
};


