#pragma once

#include "TerrainObjectManager.h"

class TerrainObject;

class TerrainManager
{
public:
	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = default;
	TerrainManager& operator=(const TerrainManager&) = default;
	~TerrainManager() {};

	TerrainObject *getTerrain() { return myTerrain; };
	void setTerrain(const char * tag) { myTerrain = TerrainObjectManager::Get(tag); };
	void DrawTerrain();

private:
	TerrainObject * myTerrain;
};