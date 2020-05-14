#pragma once

#include "../Collidable.h"

class CollisionAttorney
{
public:
	class GroupRegistration
	{
	private:
		friend class CollidableGroup;
		static CollidableGroup::StorageIterator getRef(Collidable * c) { return c->getRef(); };
		static void setRef(Collidable * c, CollidableGroup::StorageIterator it) { c->setRef(it); };
	};
	class CommandRegistration
	{
	private:
		friend class CollideRegistrationCommand;
		friend class CollideDeregistrationCommand;
		static void SceneRegistration(Collidable * c) { c->SceneRegistration(); };
		static void SceneDeregistration(Collidable * c) { c->SceneDeregistration(); };
	};
	class GetSet
	{
	private:
		friend class CollidableGroup;
		friend class CollisionTestPairCommand;
		friend class CollisionTestSelfCommand;
		friend class CollisionTestTerrainCommand;
		friend class TerrainObject;
		static 	const CollisionVolume & GetVolume(Collidable * c) { return c->GetVolume(); };
		static CollisionVolumeBSphere * GetDefaultSphere(Collidable * c) { return c->defaultSphere; };
	};
	class Collision
	{
	private:
		friend class CollisionTestTerrainCommand;
		static void CollisionTerrain(Collidable * c) { c->CollisionTerrain(); };
	};
};