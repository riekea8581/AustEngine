#pragma once

#include "..\Collision\CollisionVolumeAABB.h"

class CollisionVolumeAABB;
class TerrainRectArea;

class TerrainIterator
{
public:
	TerrainIterator()
		:xOffset(0), zOffset(0) {};
	TerrainIterator(const TerrainIterator&) = default;				 // Copy constructor
	TerrainIterator& operator=(const TerrainIterator&) & = default;  // Assignment operator
	~TerrainIterator() {};

	TerrainIterator& Increment();
	bool operator!=(const TerrainIterator & other) const;

	CollisionVolumeAABB getAABB() { return myAABB; };
	TerrainRectArea * getRect() { return myRect; };
	int getXOffset() const { return xOffset; };
	int getZOffset() const { return zOffset; };

	void setAABB(CollisionVolumeAABB aabb) { myAABB = aabb; };
	void setRect(TerrainRectArea * rect) { myRect = rect; };
	void setOffset(int x, int z);

private:
	CollisionVolumeAABB myAABB;
	TerrainRectArea * myRect;
	int xOffset;
	int zOffset;
};