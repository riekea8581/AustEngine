#pragma once

#include "Tank.h"
#include "..\AustEngine\Game Object\GameObject.h"

class Tank;
class TerrainObject;

class TankManager : public GameObject
{
public:
	TankManager() = delete;
	TankManager(const TankManager&) = delete;
	TankManager& operator=(const TankManager&) = delete;
	virtual ~TankManager();

	TankManager(const Vect & v, TerrainObject * t);

	void Override(StorageNode node);
	void DecrementHealth(int health);
	void ResetHealth() { TankHealth = TankMaxHealth; };

	virtual void Draw2D();
	virtual void Alarm0();

	Tank * GetTank() { return myTank; };
	int GetHealth() { return TankHealth; };

private:
	static const int TankMaxHealth = 8;

	static int TankHealth;

	Tank * myTank;
	Sprite * SpriteArray[TankMaxHealth];
};