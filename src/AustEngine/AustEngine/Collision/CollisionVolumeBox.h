#pragma once

#include "CollisionVolume.h"
#include "Attorneys/VisualizerAttorney.h"
#include "../MathTools/MathTools.h"

class CollisionVolumeBox : public CollisionVolume
{
	friend class BoxAttorney;
public:
	CollisionVolumeBox() {};
	CollisionVolumeBox(const CollisionVolumeBox&) = default;
	CollisionVolumeBox& operator=(const CollisionVolumeBox&) = default;
	virtual ~CollisionVolumeBox() {};
protected:
	Matrix World;
	Matrix AdjWorld;

	Vect min;
	Vect max;
	Vect trans;
	Vect rot;
	Vect scale;

	Vect HalfDiag;
	Vect Center;
	float ScaleSqr;
public:
	const Vect & GetMin() const { return min; };
	const Vect & GetMax() const { return max; };
	const Vect & GetHalfDiag() const { return HalfDiag; };
	const Vect & GetCenter() const { return Center; };
	const float & GetScaleSqr() const { return ScaleSqr; };
};