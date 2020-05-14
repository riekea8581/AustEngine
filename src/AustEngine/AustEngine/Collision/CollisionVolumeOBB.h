#pragma once

#include "CollisionVolumeBox.h"
#include "Attorneys/VisualizerAttorney.h"
#include "../MathTools/MathTools.h"

class CollisionVolumeOBB : public CollisionVolumeBox
{
public:
	CollisionVolumeOBB() {};
	CollisionVolumeOBB(const CollisionVolumeOBB&) = default;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = default;
	virtual ~CollisionVolumeOBB() {};
private:
	virtual void InitializeData(Model * mod, Matrix & mat);
	virtual void ComputeData(Model * mod, Matrix & mat);
	virtual void DebugView(const Vect& col) const { VisualizerAttorney::VizDisplay::ShowOBB(*this, col); };
	virtual bool IntersectAccept(const CollisionVolume& other) const { return other.IntersectVisit(*this); };
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const { return MathTools::Intersect(other, *this); };
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const { return MathTools::Intersect(other, *this); };
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const { return MathTools::Intersect(*this, other); };
	virtual void SendColCommand(const Vect& col) const;
};
