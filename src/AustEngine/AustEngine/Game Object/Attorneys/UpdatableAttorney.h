#pragma once

#include "../Updatable.h"

class UpdatableAttorney
{
public:
	class UpdateGameLoop
	{
	private:
		friend class UpdatableManager;
		static void Update(Updatable * d) { d->Update(); };
		static UpdatableManager::StorageIterator getRef(Updatable * d) { return d->getRef(); };
		static void setRef(Updatable * d, UpdatableManager::StorageIterator it) { d->setRef(it); };
	};
	class UpdateRegistration
	{
	private:
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
		static void SceneRegistration(Updatable * d) { d->SceneRegistration(); };
		static void SceneDeregistration(Updatable * d) { d->SceneDeregistration(); };
	};
};