#include "..\..\Attorneys\CollisionAttorney.h"
#include "CollisionTestTerrainCommand.h"
#include "..\..\Managers\CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "..\..\..\Collision\CollisionVolumeBSphere.h"
#include "..\..\..\Collision\Attorneys\VolumeAttorney.h"
#include "..\..\..\Terrain\TerrainObject.h"
#include "..\..\..\Terrain\TerrainRectArea.h"
#include "..\..\..\Terrain\TerrainIterator.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup * g)
	: pG(g)
{ }

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{

}

void CollisionTestTerrainCommand::execute()
{
	const TerrainObject * terrain = SceneManager::GetCurrentScene()->getTerrain();
	const CollidableGroup::CollidableCollection & Collection = pG->GetColliderCollection();

	for (auto it = Collection.begin(); it != Collection.end(); it++)
	{
		Vect center = CollisionAttorney::GetSet::GetDefaultSphere((*it))->GetCenter();
		float radius = CollisionAttorney::GetSet::GetDefaultSphere((*it))->GetRadius();
		TerrainRectArea candidateCells = TerrainRectArea(terrain, Vect(center.X() + radius, center.Y() + radius, center.Z() + radius),
			Vect(center.X() - radius, center.Y() - radius, center.Z() - radius));
		for (TerrainIterator itCell = candidateCells.Begin(); itCell != candidateCells.End(); itCell = itCell.Increment())
		{
			if (VolumeAttorney::Intersect(itCell.getAABB(), CollisionAttorney::GetSet::GetVolume((*it))))
			{
				CollisionAttorney::Collision::CollisionTerrain(*it);
				return;
			}
		}
	}
}