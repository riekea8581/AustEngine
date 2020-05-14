#pragma once

#include <list>

class Drawable;
class Sprite;

class DrawableManager
{
private:
	typedef std::list<Drawable*> StorageList;

	StorageList storageList;

public:
	typedef StorageList::iterator StorageIterator; 

	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;
	~DrawableManager() {};

	void ProcessElements();

	void Register(Drawable * dr);
	void Deregister(Drawable * dr);
};