#include "..\..\Attorneys\CollisionAttorney.h"
#include "CollisionTestSelfCommand.h"
#include "..\..\Managers\CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "..\..\..\Collision\CollisionVolumeBSphere.h"
#include "..\..\..\Collision\Attorneys\VolumeAttorney.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup * g, CollisionDispatchBase * pd)
	: pG(g), pDispatch(pd)
{ }

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::execute()
{
	const CollidableGroup::CollidableCollection & Collection = pG->GetColliderCollection();

	for (auto it1 = Collection.begin(); it1 != Collection.end(); it1++)
	{
		const CollisionVolume & vol1 = CollisionAttorney::GetSet::GetVolume((*it1)); 
		for (auto it2 = std::next(it1, 1); it2 != Collection.end(); it2++)
		{
			const CollisionVolume & vol2 = CollisionAttorney::GetSet::GetVolume((*it2));

			if (!(VolumeAttorney::Intersect(*CollisionAttorney::GetSet::GetDefaultSphere((*it1)), *CollisionAttorney::GetSet::GetDefaultSphere((*it2))))) return;

			if (VolumeAttorney::Intersect(vol1, vol2))
			{
				pDispatch->ProcessCallbacks(*it1, *it2);
			}
		}
	}
}