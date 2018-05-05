#pragma once
#include "System.h"
#include "EffectBase.h"

class SpriteSystem : public System<PositionComponent, SpriteComponent>
{
public:
	SpriteSystem();
	~SpriteSystem();

	virtual void OperateEntities(EntityManager& entityManager, TimeSlotInSecond dt) override;

private:
	PlainEffect			mEffect;
	ID3D11Buffer*		mVertexBuffer;
	ID3D11Buffer*		mIndexBuffer;
	Count					mIndicesCount;
	ID3D11InputLayout* mInputLayout;
};