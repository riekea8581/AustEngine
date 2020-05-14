#include "TerrainIterator.h"
#include "TerrainRectArea.h"
#include "TerrainObject.h"

TerrainIterator& TerrainIterator::Increment()
{
	xOffset++;
	if (xOffset > myRect->getXLen() && zOffset != myRect->getZLen())
	{
		xOffset = 0;
		zOffset++;
	}
	myAABB = myRect->getTerrain()->getAABB(myRect->getStart(), xOffset, zOffset);
	return *this;
}

bool TerrainIterator::operator!=(const TerrainIterator & other) const
{
	return (xOffset != other.getXOffset() || zOffset != other.getZOffset());
}

void TerrainIterator::setOffset(int x, int z)
{
	xOffset = x;
	zOffset = z;
}