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
	bool GetIsFullScreen() const;
	void SetIsFullScreen(bool par);
	bool GetIsAntiAlias() const;
	void SetIsAntiAlias(bool par);
	AntiAliasType GetAntiAliasType() const;
	void SetAntiAliasType(AntiAliasType par);

	//��ò������õ����п�ѡ��
	Array<Size2D> GetAllResolutions() const;
	Array<AntiAliasType> GetAllAntiAliasType() const;
	Array<int> GetAllAntiAliasLevel() const;

private:
	//���õ���ʱֵ
	Size2D mResolution;
	int mRefreshRate;
	int mAntiAliasLevel;
	bool mIsFullScreen;
	bool mIsAntiAlias;
	AntiAliasType mAntiAliasType;

	//JSON��д��
	JsonCommunicator mFile;
};


