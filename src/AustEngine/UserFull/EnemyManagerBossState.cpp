#include "EnemyManagerBossState.h"
#include "..\AustEngine\Sprite\Sprite.h"
#include "..\AustEngine\UI Helper\UIHelper.h"

void EnemyManagerBossState::LoadSprite()
{
	mySprite = new Sprite(("redBar"));
	mySprite->SetScaleFactor(SpriteScale, SpriteScale);
}

void EnemyManagerBossState::DrawHealthBar(int , int health)
{
	UIHelper::DrawHealthBar(mySprite, SpriteXPos, SpriteYPos, SpriteXTrans, health);
}

bool EnemyManagerBossState::CheckDeath(Enemy * e, int )
{
	return (e == nullptr);
}

EnemyManagerBossState::~EnemyManagerBossState()
{
	delete mySprite;
}