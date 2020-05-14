#include "CollidableGroup.h"
#include "../Collidable.h"
#include "../Attorneys/CollisionAttorney.h"
#include "../../Collision/CollisionVolumeAABB.h"
#include "../../Collision/Attorneys/AABBAttorney.h"

CollidableGroup::CollidableGroup()
{
	AABBColor = Vect(0, 1.0f, 0);
	myAABB = new CollisionVolumeAABB();
}

void CollidableGroup::Register(Collidable *col)
{
	CollisionAttorney::GroupRegistration::setRef(col, collideCol.insert(collideCol.end(), col));
}

void CollidableGroup::Deregister(Collidable * col)
{
	collideCol.erase(CollisionAttorney::GroupRegistration::getRef(col));
}

void CollidableGroup::ComputeAABB()
{
	if (collideCol.size() == 0) return;
	StorageIterator it = collideCol.begin();
	AABBAttorney::ComputeData(myAABB, CollisionAttorney::GetSet::GetDefaultSphere(*it));
	float minX = myAABB->GetMin().X();
	float minY = myAABB->GetMin().Y();
	float minZ = myAABB->GetMin().Z();
	float maxX = myAABB->GetMax().X();
	float maxY = myAABB->GetMax().Y();
	float maxZ = myAABB->GetMax().Z();
	it++;
	while(it != collideCol.end())
	{
		AABBAttorney::ComputeData(myAABB, CollisionAttorney::GetSet::GetDefaultSphere(*it));
		if (myAABB->GetMin().X() < minX) minX = myAABB->GetMin().X();
		if (myAABB->GetMax().X() > maxX) maxX = myAABB->GetMax().X();
		if (myAABB->GetMin().Y() < minY) minY = myAABB->GetMin().Y();
		if (myAABB->GetMax().Y() > maxY) maxY = myAABB->GetMax().Y();
		if (myAABB->GetMin().Z() < minZ) minZ = myAABB->GetMin().Z();
		if (myAABB->GetMax().Z() > maxZ) maxZ = myAABB->GetMax().Z();
		it++;
	}
	AABBAttorney::ComputeData(myAABB, minX, minY, minZ, maxX, maxY, maxZ);
	VolumeAttorney::SendColCommand(*myAABB, AABBColor);
}

const CollisionVolumeAABB & CollidableGroup::GetAABB()
{
	return *myAABB;
}

CollidableGroup::~CollidableGroup()
{
	delete myAABB;
}