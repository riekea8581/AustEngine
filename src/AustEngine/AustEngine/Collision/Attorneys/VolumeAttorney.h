#pragma once

#include "../CollisionVolume.h"

class VolumeAttorney
{
	friend class Visualizer;
	friend class Collidable;
	friend class CollidableGroup;
	friend class CollisionTestPairCommand;
	friend class CollisionTestSelfCommand;
	friend class CollisionTestTerrainCommand;
private:
	static void DebugView(const CollisionVolume &v, Vect &col) { v.DebugView(col); };
	static void InitializeData(CollisionVolume &v, Model * mod, Matrix & mat) { v.InitializeData(mod, mat); };
	static void ComputeData(CollisionVolume &v, Model * mod, Matrix & mat) { v.ComputeData(mod, mat); };
	static bool Intersect(const CollisionVolume &self, const CollisionVolume & other) { return self.IntersectAccept(other); };
	static void SendColCommand(const CollisionVolume &self, Vect col) { self.SendColCommand(col); };
};