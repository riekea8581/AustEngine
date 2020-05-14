#include "TerrainRectArea.h"
#include "TerrainObject.h"
#include "TerrainIterator.h"

TerrainRectArea::TerrainRectArea(const TerrainObject * t, Vect min, Vect max)
{
	myTerrain = t;
	start = myTerrain->HighlightCell(min);
	end = myTerrain->HighlightCell(max);
	xLen = myTerrain->getXLen(start, end);
	zLen = myTerrain->getZLen(start, end);
}

TerrainIterator TerrainRectArea::Begin()
{
	TerrainIterator tmp;
	tmp.setRect(this);
	tmp.setAABB(myTerrain->getAABB(start, 0, 0));
	return tmp;
}

TerrainIterator TerrainRectArea::End()
{
	TerrainIterator tmp;
	tmp.setRect(this);
	tmp.setOffset(xLen + 1, zLen);
	return tmp;
}
