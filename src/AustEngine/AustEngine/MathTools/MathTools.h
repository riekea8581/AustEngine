#pragma once

#include "AzulCore.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeBox;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class MathTools
{
public:
	static bool Intersect(const CollisionVolume & A, const CollisionVolume & B); 
	static bool Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeBSphere & B);
	static bool Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeAABB & B);
	static bool Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeOBB & B);
	static bool Intersect(const CollisionVolumeAABB & A, const CollisionVolumeAABB & B);
	static bool Intersect(const CollisionVolumeAABB & A, const CollisionVolumeOBB & B);
	static bool Intersect(const CollisionVolumeOBB & A, const CollisionVolumeOBB & B);
	static bool Intersect(const Vect & A, const CollisionVolumeAABB & B);
	static bool Intersect(const Vect & A, const CollisionVolumeOBB & B);

	static float Clamp(float target, float min, float max);
	static Vect ClampPoint(Vect target, Vect min, Vect max);
	static bool TestIntervalOverlap(float minA, float maxA, float minB, float maxB);
	static bool SATCheck(Vect v, const CollisionVolumeBox & A, const CollisionVolumeBox & B);
	static float ProjMax(Vect v, const CollisionVolumeBox & A, const Matrix & inv);
};