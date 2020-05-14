#include "..\..\Collidable.h"
#include "..\..\Attorneys\CollisionAttorney.h"
#include "CollisionTestPairCommand.h"
#include "..\..\Managers\CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "..\..\..\Collision\CollisionVolumeBSphere.h"
#include "..\..\..\Collision\CollisionVolumeAABB.h"
#include "..\..\..\Collision\Attorneys\VolumeAttorney.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup * g1, CollidableGroup * g2, CollisionDispatchBase * pd)
	: pG1(g1), pG2(g2), pDispatch(pd)
{ }

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::execute()
{
	const CollidableGroup::CollidableCollection & Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::CollidableCollection & Collection2 = pG2->GetColliderCollection();

	if (!(VolumeAttorney::Intersect(pG1->GetAABB(), pG2->GetAABB()))) return;

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		const CollisionVolume & vol1 = CollisionAttorney::GetSet::GetVolume((*it1));
		
		if (VolumeAttorney::Intersect(*CollisionAttorney::GetSet::GetDefaultSphere((*it1)), pG2->GetAABB()))
		{
			for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
			{
				const CollisionVolume & vol2 = CollisionAttorney::GetSet::GetVolume((*it2));

				if (VolumeAttorney::Intersect(*CollisionAttorney::GetSet::GetDefaultSphere((*it1)), *CollisionAttorney::GetSet::GetDefaultSphere((*it2))))
				{
					if (VolumeAttorney::Intersect(vol1, vol2))
					{
						pDispatch->ProcessCallbacks(*it1, *it2);
					}
				}
			}
		}
	}
}