#pragma once

#include "EnemyManagerState.h"

class EnemyManagerBaseState : public EnemyManagerState
{
public:
	EnemyManagerBaseState() {};
	EnemyManagerBaseState(const EnemyManagerBaseState&) = delete;
	EnemyManagerBaseState& operator=(const EnemyManagerBaseState&) = delete;
	virtual ~EnemyManagerBaseState();

	virtual void LoadSprite();
	virtual void DrawHealthBar(int count, int);
	virtual bool CheckDeath(Enemy * e, int count) override;

private:
	float SpriteXPos = 75;
	float SpriteYPos = 550;
	float SpriteXTrans = 100;
};