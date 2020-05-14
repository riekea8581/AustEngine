#pragma once

#include "..\Game Object\Drawable.h"

class SpriteRegistrationCommand;
class SpriteDeregistrationCommand;

class Sprite
{
public:
	Sprite() = delete;
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	virtual ~Sprite() { delete pGOSprite; };
	
	/// \brief A constructor for a sprite object. This object is 2D and will always be drawn by the orthographic
	/// camera.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// The Sprite constructor is used to initialize a Sprite object. A C-string tag is passed into the constructor,
	/// which is used to get the sprite from the Image Manager. The image needs to be loaded in the LoadResources
	/// function in order to actually be used. The sprite, when drawn, will show up on the orthographic camera and
	/// will be overlaid on top of any normal game objects.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being created using the "Fireball" image.
	///
	/// \code
	/// 
	/// void Object::Object()
	/// {
	///		Sprite * mySprite = new Sprite("Fireball");
	/// }
	/// \endcode
	Sprite(std::string imgKey);
	
	// Current Implementation: Rather than derived classes, all sprite objects simply use the sprite class;
	// Thus these should all be public rather than protected
	
	/// \brief A function that must be called in order to actually display a given sprite.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// The Render function is called from within another object's Draw2D function. Note that since sprites
	/// are not game objects, this must be done manually for each sprite or that sprite will not be drawn. Also,
	/// this must specifically be called from the Drawable::Draw2D function, NOT the Drawable::Draw function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being rendered properly.
	///
	/// \code
	/// 
	/// void Object::Draw2D()
	/// {
	///		mySprite->Render();
	/// }
	/// \endcode
	void Render();

	float GetAngle() { return angle; };
	/// \brief A function that determines the angle at which a sprite is rendered.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// A sprite can be rotated clockwise (in radians) if the user so desires. In order to do this, simply
	/// call the SetAngle() function and pass in the radians to rotate by as the parameter.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being set to rotate by 90 degrees clockwise.
	///
	/// \code
	/// 
	/// void Object::InitializeSprite()
	/// {
	///		mySprite->SetAngle(M_PI / 2);
	/// }
	/// \endcode
	void SetAngle(float a) { angle = a; };
	/// \brief A function that determines the "center" (or origin) of the sprite.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// By default, the position of a sprite means that the corner of a sprite will be at a
	/// given x & y value. This is not always ideal, so the user can redefine what pixel of
	/// a sprite will be at the position value also defined by the user (see below). This will
	/// generally be set to the center of the sprite or as close as possible, but can be set
	/// to anywhere the user wants.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite's center being set to the pixel at XY position
	/// (2, 2) on the sprite.
	///
	/// \code
	/// 
	/// void Object::InitializeSprite()
	/// {
	///		mySprite->SetCenter(2, 2);
	/// }
	/// \endcode
	void SetCenter(float x, float y);
	/// \brief A function that determines where on the screen a sprite is drawn.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// A sprite can be drawn at any XY value by simply passing the X & Y values into this
	/// function. Specifically, the center pixel (described above) of the sprite will be
	/// positioned at the X & Y values passed in here.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being positioned at XY position (2, 2).
	///
	/// \code
	/// 
	/// void Object::InitializeSprite()
	/// {
	///		mySprite->SetPos(2, 2);
	/// }
	/// \endcode
	void SetPosition(float x, float y);
	/// \brief A function that determines the scale of a sprite.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// A sprite can be scaled (from a default value of 1x) along the X and Y axes. Unlike
	/// normal game objects, the X and Y axes of the sprite can be scaled separately with no
	/// issue, since sprites do not need to collide with anything (whereas non-uniform scaling
	/// messes with game object collision).
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being scaled 2x along the X-axis and 1x along the
	/// Y-axis.
	///
	/// \code
	/// 
	/// void Object::InitializeSprite()
	/// {
	///		mySprite->SetScaleFactor(2, 1);
	/// }
	/// \endcode
	void SetScaleFactor(float x, float y);
	/// \brief A function that determines the scale of a sprite, in pixels.
	/// 
	/// \ingroup SPRITEEVENTS
	/// 
	/// A sprite can also be scaled to be a certain number of pixels wide and tall. This function
	/// takes two floats, with the first determining the new length of the sprite in pixels and the
	/// second determining the new height of the sprite in pixels.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a Sprite being scaled to be 100 pixels wide and 50 pixels tall.
	///
	/// \code
	/// 
	/// void Object::InitializeSprite()
	/// {
	///		mySprite->SetScalePixel(100, 50);
	/// }
	/// \endcode
	void SetScalePixel(float x, float y);
	float GetWidth() { return pGOSprite->origWidth; };

private:
	GraphicsObject_Sprite * pGOSprite;

	float centerX;
	float centerY;

	float posX;
	float posY;
	
	float scaleX;
	float scaleY;
	
	float angle;
	
};