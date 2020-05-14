#pragma once

#include "AzulCore.h"
#include <list>

class Collidable;
class CollisionVolumeAABB;

class CollidableGroup : public Align16
{

public:
	typedef std::list<Collidable*> CollidableCollection; 
	typedef CollidableCollection::iterator StorageIterator;

private:
	CollidableCollection collideCol;
	CollisionVolumeAABB * myAABB;
	Vect AABBColor;
public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;
	~CollidableGroup();

	void Register(Collidable * col);
	void Deregister(Collidable * col);

	const CollidableCollection &GetColliderCollection() { return collideCol; };
	const CollisionVolumeAABB & GetAABB();

	void ComputeAABB();
};