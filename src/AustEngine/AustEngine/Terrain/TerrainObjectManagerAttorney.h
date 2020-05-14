#pragma once

#include "TerrainObjectManager.h"

class TerrainObjectManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { TerrainObjectManager::Delete(); };
};