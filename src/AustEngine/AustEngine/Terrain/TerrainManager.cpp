#include "TerrainManager.h"
#include "TerrainObject.h"

void TerrainManager::DrawTerrain()
{
	if(myTerrain != nullptr)
		myTerrain->Draw();
}