#pragma once

#include "AzulCore.h"

class TerrainObject;
class TerrainIterator;

class TerrainRectArea
{
public:
	TerrainRectArea() = delete;										 // Default constructor
	TerrainRectArea(const TerrainRectArea&) = default;				 // Copy constructor
	TerrainRectArea& operator=(const TerrainRectArea&) & = default;  // Assignment operator
	~TerrainRectArea() {};

	TerrainRectArea(const TerrainObject * t, Vect min, Vect max);

	TerrainIterator Begin();
	TerrainIterator End();

	const TerrainObject * getTerrain() { return myTerrain; };
	int getStart() { return start; };
	int getXLen() { return xLen; };
	int getZLen() { return zLen; };

private:
	const TerrainObject * myTerrain;
	int start;
	int end;
	int xLen;
	int zLen;
};