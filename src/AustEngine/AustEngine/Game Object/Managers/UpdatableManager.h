#pragma once

#include <list>

class Updatable;

class UpdatableManager
{
private:
	typedef std::list<Updatable*> StorageList;

	StorageList storageList;
public:
	typedef StorageList::iterator StorageIterator; 
	
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;
	~UpdatableManager() {};

	void ProcessElements();

	void Register(Updatable * up);
	void Deregister(Updatable * up);
};