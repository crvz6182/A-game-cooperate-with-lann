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


	//��ȡ�ͱ�������
	virtual void GetConfig() override;
	virtual void SetConfig() override;

	//��ú��޸ĸ������õ���ʱֵ
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

	//��ò������õ����п�ѡ��
	Array<Size2D> GetAllResolutions() const;
	Array<AntiAliasType> GetAllAntiAliasType() const;
	Array<int> GetAllAntiAliasLevel() const;

private:
	//���õ���ʱֵ
	int mResolution[2];
	int mRefreshRate;
	int mAntiAliasLevel;
	FullScreenSetting mIsFullScreen;
	AntiAliasSetting mIsAntiAlias;
	AntiAliasType mAntiAliasType;

	//JSON��д��
	JsonCommunicator mFile;
};


