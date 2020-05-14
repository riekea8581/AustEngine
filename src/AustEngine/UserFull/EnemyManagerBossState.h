#pragma once

#include "EnemyManagerState.h"

class EnemyManagerBossState : public EnemyManagerState
{
public:
	EnemyManagerBossState() {};
	EnemyManagerBossState(const EnemyManagerBossState&) = delete;
	EnemyManagerBossState& operator=(const EnemyManagerBossState&) = delete;
	virtual ~EnemyManagerBossState();

	virtual void LoadSprite();
	virtual void DrawHealthBar(int , int health);
	virtual bool CheckDeath(Enemy * e, int count) override;

private:
	float SpriteXPos = 75;
	float SpriteYPos = 550;
	float SpriteXTrans = 25;
};