#pragma once

#include "CollisionVolume.h"
#include "Attorneys/VisualizerAttorney.h"
#include "../MathTools/MathTools.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere()
		:center(Vect(0, 0, 0)), radius(0) {};
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = default;
	virtual ~CollisionVolumeBSphere() {};
private:
	Vect center;
	float radius;

	virtual void InitializeData(Model * mod, Matrix & mat) { ComputeData(mod, mat); };
	virtual void ComputeData(Model * mod, Matrix & mat);
	virtual void DebugView(const Vect& col) const { VisualizerAttorney::VizDisplay::ShowBSphere(*this, col); };
	virtual bool IntersectAccept(const CollisionVolume& other) const { return other.IntersectVisit(*this); };
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const { return MathTools::Intersect(*this, other); };
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const { return MathTools::Intersect(*this, other); };
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const { return MathTools::Intersect(*this, other); };
	virtual void SendColCommand(const Vect& col) const;
public:
	const Vect & GetCenter() const { return center; };
	float GetRadius() const { return radius; };
};
