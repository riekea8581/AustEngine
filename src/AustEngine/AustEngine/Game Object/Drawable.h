#pragma once

#include "..\Scene\SceneManager.h"
#include "Managers\DrawableManager.h"
#include "RegState.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
public:
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable();
protected:
	/// \brief Called by a game object to indicate that it wishes to be drawn each frame.
	/// 
	/// \ingroup DRAWEVENTS
	/// 
	/// A game object must indicate that it wishes to be drawn by the active scene each frame in order for its
	/// Draw function to be called. This is done using the SubmitSceneRegistration function. Generally this
	/// function is called either upon creation or (more likely) upon scene entry.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneEntry function that ONLY calls for the given object to be drawn,
	/// not updated or any other game object functionality.
	///
	/// \code
	/// 
	/// void Object::SceneEntry()
	/// {
	///		Drawable::SubmitSceneRegistration();
	/// }
	/// \endcode
	void SubmitSceneRegistration();
	/// \brief Called by a game object to indicate that it no longer wishes to be drawn each frame.
	/// 
	/// \ingroup DRAWEVENTS
	/// 
	/// A game object must indicate that it wishes to stop being drawn by the active scene each frame,
	/// or its Draw function will continue to be called. This is done using the SubmitSceneDeregistration
	/// function. Generally this function is called upon scene exit.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SceneExit function that ONLY calls for the given object to stop being
	/// drawn, not updated or any other game object functionality.
	///
	/// \code
	/// 
	/// void Object::SceneExit()
	/// {
	///		Drawable::SubmitSceneDeregistration();
	/// }
	/// \endcode
	void SubmitSceneDeregistration();
private:
	friend class DrawableAttorney;

	RegState state;

	DrawRegistrationCommand * regCommand;
	DrawDeregistrationCommand * deregCommand;

	/// \brief A game object function that will be called once per frame with the explicit purpose of
	/// rendering that object onscreen.
	/// 
	/// \ingroup DRAWEVENTS
	/// 
	/// The Drawable::Draw function is an empty virtual function intended to be overridden by any game
	/// object that wishes to be drawn in a scene. The Draw function should ONLY contain code relevant to
	/// rendering the given game object; all other code can go in the Updatable::Update function. Generally,
	/// the Draw function will involve calling Model::Render on a local model, passing in the current scene's
	/// active camera as a parameter.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Draw function that causes a given game object to be rendered onscreen.
	///
	/// \code
	/// 
	/// void Object::Draw()
	/// {
	///		myModel->Render(SceneManager::GetCurrentScene()->getCamera());
	/// }
	/// \endcode
	virtual void Draw() {}; 
	/// \brief A game object function that will be called once per frame with the explicit purpose of
	/// rendering all 2D images associated with a given Drawable object.
	/// 
	/// \ingroup DRAWEVENTS
	/// 
	/// The Drawable::Draw2D function is an empty virtual function intended to be overridden by any game
	/// object that wishes to render Sprites or SpriteStrings within a scene. The Draw2D function should ONLY
	/// contain code relevant to drawing sprites, NOT Models or anything else. Such code can go in the Drawable::Draw
	/// function. Generally, the Draw2D function will involve calling Sprite::Render or SpriteString::Render on any
	/// such objects associated with the caller, with no camera parameter being necessary this time.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Draw2D function that causes a given game object to render an associated Sprite
	/// and SpriteString.
	///
	/// \code
	/// 
	/// void Object::Draw2D()
	/// {
	///		mySprite->Render();
	///     myString->Render();
	/// }
	/// \endcode
	virtual void Draw2D() {};
	
	void SceneRegistration();
	void SceneDeregistration();

	DrawableManager::StorageIterator myRef;
	DrawableManager::StorageIterator getRef() { return myRef; };
	void setRef(DrawableManager::StorageIterator it) { myRef = it; };
};