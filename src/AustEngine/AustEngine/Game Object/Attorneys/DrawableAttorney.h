#pragma once

#include "../Drawable.h"

class DrawableAttorney
{
public:
	class DrawGameLoop
	{
	private:
		friend class DrawableManager;
		static void Draw(Drawable * d) { d->Draw(); };
		static void Draw2D(Drawable * d) { d->Draw2D(); };
		static DrawableManager::StorageIterator getRef(Drawable * d) { return d->getRef(); };
		static void setRef(Drawable * d, DrawableManager::StorageIterator it) { d->setRef(it); };
	};
	class DrawRegistration
	{
	private:
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand; 
		static void SceneRegistration(Drawable * d) { d->SceneRegistration(); };
		static void SceneDeregistration(Drawable * d) { d->SceneDeregistration(); };
	};
};