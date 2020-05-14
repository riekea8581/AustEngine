#include "EnemyManagerBaseState.h"
#include "..\AustEngine\Sprite\Sprite.h"
#include "..\AustEngine\UI Helper\UIHelper.h"

void EnemyManagerBaseState::LoadSprite()
{
	mySprite = new Sprite(("redTank"));
	mySprite->SetScaleFactor(SpriteScale, SpriteScale);
}

void EnemyManagerBaseState::DrawHealthBar(int count, int)
{
	UIHelper::DrawHealthBar(mySprite, SpriteXPos, SpriteYPos, SpriteXTrans, count);
}

bool EnemyManagerBaseState::CheckDeath(Enemy * , int count)
{
	return (count == 0);
}

EnemyManagerBaseState::~EnemyManagerBaseState()
{
	delete mySprite;
}