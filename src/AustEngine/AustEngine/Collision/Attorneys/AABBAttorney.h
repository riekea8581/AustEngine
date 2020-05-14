#pragma once

#include "../CollisionVolumeAABB.h"

class AABBAttorney
{
	friend class CollidableGroup;
	friend class TerrainObject;
private:
	static void ComputeData(CollisionVolumeAABB * b, CollisionVolumeBSphere * s) { b->ComputeData(s); };
	static void ComputeData(CollisionVolumeAABB * b, float minX, float minY, float minZ, float maxX, float maxY, float maxZ) { b->ComputeData(minX, minY, minZ, maxX, maxY, maxZ); };
};