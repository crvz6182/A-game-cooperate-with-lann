#pragma once
#include "stdafx.h"
#include "String.h"
#include "Math.h"
#include "FileIO.h"
#include <string>

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
	bool GetIsFullScreen() const;
	void SetIsFullScreen(bool par);
	bool GetIsAntiAlias() const;
	void SetIsAntiAlias(bool par);
	AntiAliasType GetAntiAliasType() const;
	void SetAntiAliasType(AntiAliasType par);

	//获得部分设置的所有可选项
	Array<Size2D> GetAllResolutions() const;
	Array<AntiAliasType> GetAllAntiAliasType() const;
	Array<int> GetAllAntiAliasLevel() const;

private:
	//设置的临时值
	Size2D mResolution;
	int mRefreshRate;
	int mAntiAliasLevel;
	bool mIsFullScreen;
	bool mIsAntiAlias;
	AntiAliasType mAntiAliasType;

	//JSON读写类
	JsonCommunicator mFile;
};


