#pragma once

#include "AzulCore.h"

class Model;
class Matrix;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume : public Align16
{
	friend class VolumeAttorney;
public:
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
protected:
	virtual void InitializeData(Model *, Matrix &) = 0;
	virtual void ComputeData(Model *, Matrix &) = 0;
private:
	virtual void DebugView(const Vect& col) const = 0;
	virtual void SendColCommand(const Vect& col) const = 0;
};
