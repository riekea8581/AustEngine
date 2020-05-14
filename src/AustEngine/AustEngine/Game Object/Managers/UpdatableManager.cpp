#include "UpdatableManager.h"
#include "../Updatable.h"
#include "../Attorneys/UpdatableAttorney.h"

void UpdatableManager::ProcessElements()
{
	for (StorageIterator it = storageList.begin(); it != storageList.end(); it++)
		UpdatableAttorney::UpdateGameLoop::Update(*it);
}

void UpdatableManager::Register(Updatable * up)
{
	UpdatableAttorney::UpdateGameLoop::setRef(up, storageList.insert(storageList.end(), up));
}

void UpdatableManager::Deregister(Updatable * up)
{
	storageList.erase(UpdatableAttorney::UpdateGameLoop::getRef(up));
}