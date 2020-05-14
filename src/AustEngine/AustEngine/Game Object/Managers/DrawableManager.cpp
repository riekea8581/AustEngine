#include "DrawableManager.h"
#include "../Drawable.h"
#include "../../Sprite/Sprite.h"
#include "../Attorneys/DrawableAttorney.h"

void DrawableManager::ProcessElements()
{
	for (StorageIterator it = storageList.begin(); it != storageList.end(); it++)
		DrawableAttorney::DrawGameLoop::Draw(*it);
	for (StorageIterator it = storageList.begin(); it != storageList.end(); it++)
		DrawableAttorney::DrawGameLoop::Draw2D(*it);
}

void DrawableManager::Register(Drawable * dr)
{
	DrawableAttorney::DrawGameLoop::setRef(dr, storageList.insert(storageList.end(), dr));
}

void DrawableManager::Deregister(Drawable * dr)
{
	storageList.erase(DrawableAttorney::DrawGameLoop::getRef(dr));
}