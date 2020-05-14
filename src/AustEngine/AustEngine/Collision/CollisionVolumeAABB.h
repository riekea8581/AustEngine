#pragma once

#include "CollisionVolumeBox.h"
#include "Attorneys/VisualizerAttorney.h"
#include "../MathTools/MathTools.h"

class CollisionVolumeAABB : public CollisionVolumeBox
{
	friend class AABBAttorney;
public:
	CollisionVolumeAABB() {};
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = default;
	virtual ~CollisionVolumeAABB() {};
private:
	virtual void InitializeData(Model * mod, Matrix & mat);
	virtual void ComputeData(Model * mod, Matrix & mat);
	void ComputeData(CollisionVolumeBSphere * s);
	void ComputeData(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	virtual void DebugView(const Vect& col) const { VisualizerAttorney::VizDisplay::ShowAABB(*this, col); };
	virtual bool IntersectAccept(const CollisionVolume& other) const { return other.IntersectVisit(*this); };
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const { return MathTools::Intersect(other, *this); };
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const { return MathTools::Intersect(*this, other); };
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const { return MathTools::Intersect(*this, other); };
	virtual void SendColCommand(const Vect& col) const;
};
