#pragma once

#include "../CollisionVolumeBox.h"

class BoxAttorney
{
	friend class Visualizer;
	friend class MathTools;
private:
	static const Matrix & GetWorld(const CollisionVolumeBox &b) { return b.World; };
	static const Matrix & GetAdjWorld(const CollisionVolumeBox &b) { return b.AdjWorld; };
};