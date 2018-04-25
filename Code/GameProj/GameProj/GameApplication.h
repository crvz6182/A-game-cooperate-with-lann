#pragma once
#include "DirectApplicationBase.h"
#include "GameWorld.h"
#include "Log.h"

class GameApplication : public DirectApplicationBase
{
public:
	GameApplication(HINSTANCE hInstance);
	virtual ~GameApplication() override;

	virtual bool Initialize() override;

	virtual void Update(TimeSlotInSecond deltaSecond) override;

	virtual void Draw() override;

	virtual void OnResize() override;

private:

	//��ʼ��Direct����
	bool InitializeDirectInput();

protected:
	HIDInput*								mInput;							//����
	GameWorld*							mGameWorld;
};

