#pragma once

class Enemy;
class Sprite;

class EnemyManagerState
{
public:
	EnemyManagerState() {};
	EnemyManagerState(const EnemyManagerState&) = delete;
	EnemyManagerState& operator=(const EnemyManagerState&) = delete;
	virtual ~EnemyManagerState() {};

	virtual void LoadSprite() {};
	virtual void DrawHealthBar(int , int) {};
	virtual bool CheckDeath(Enemy *, int) { return false; };

protected:
	Sprite * mySprite;
	float SpriteScale = 0.5f;
};