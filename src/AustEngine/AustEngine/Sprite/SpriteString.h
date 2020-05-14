#pragma once

#include <map>
#include <string>

class Sprite;
class SpriteFont;

class SpriteString
{
public:
	SpriteString() = delete;
	SpriteString(const SpriteString&) = delete;
	SpriteString& operator=(const SpriteString&) = delete;
	virtual ~SpriteString() {};

	SpriteString(const SpriteFont&);
	/// \brief The constructor for the SpriteString object, which takes a font, a C-string, and an
	/// X & Y value for position.
	/// 
	/// \ingroup SPRITESTRING
	/// 
	/// The SpriteString object draws a string of letter sprites on the screen in order to spell out
	/// a given string. Four values are needed to initialize this object: a font TGA to use (as loaded
	/// by the Sprite Font Manager), a string to spell, and an X & Y value to draw the string at.
	/// Then, when rendered, the string will be drawn using the given font.
	///
	/// \par Example:
	/// 
	/// The following example depicts a SpriteString being created with the MyFont font and set to display
	/// "Hello" at XY position (100, 100).
	///
	/// \code
	/// 
	/// void Object::Object()
	/// {
	///		SpriteString * s = new SpriteString(SpriteFontManager::Get("MyFont"), "Hello", 100, 100);
	/// }
	/// \endcode
	SpriteString(SpriteFont * sf, std::string s, int x, int y);

	/// \brief A function that must be called in order to actually display a given spritestring.
	/// 
	/// \ingroup SPRITESTRING
	/// 
	/// Like with a normal sprite, the Render function is called from within another object's Draw2D function.
	/// Again, this must be done manually for each spritestring. Also, this must specifically be called from the
	/// Drawable::Draw2D function, NOT the Drawable::Draw function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SpriteString being rendered properly.
	///
	/// \code
	/// 
	/// void Object::Draw2D()
	/// {
	///		mySpriteString->Render();
	/// }
	/// \endcode
	void Render();

	int GetWidth() { return width; };
	int GetHeight() { return height; };
	/// \brief A function that can be used to set a new position for a sprite string.
	/// 
	/// \ingroup SPRITESTRING
	/// 
	/// This function is to be called if the user wishes to change the position of a sprite string after it is
	/// created. Like in the constructor, the two ints represent the X & Y position of the string. This can be
	/// used to change a sprite string's location mid-scene.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SpriteString being set to render at position (0, 0).
	///
	/// \code
	/// 
	/// void Object::Draw2D()
	/// {
	///		mySpriteString->Set(0, 0);
	/// }
	/// \endcode
	void Set(int x, int y);
	/// \brief A function that can be used to set all parameters of a sprite string.
	/// 
	/// \ingroup SPRITESTRING
	/// 
	/// This function is to be called if the user wishes to completely redefine an existing sprite string without
	/// creating a new one. The parameters are the same as in the SpiteString constructor, and can be used to
	/// completely override an existing sprite string.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a SpriteString being set to render "Goodbye" at position (0, 0), with the
	/// "Font2" font.
	///
	/// \code
	/// 
	/// void Object::Draw2D()
	/// {
	///		mySpriteString->Set(SpriteFontManager::Get("Font2"), "Goodbye", 0, 0);
	/// }
	/// \endcode
	void Set(SpriteFont * sf, std::string s, int x, int y);
private:
	typedef int Key;
	typedef Sprite Glyph; 
	typedef std::map<Key, Glyph *> GlyphCollection;
	GlyphCollection glyphs;
	
	SpriteFont * sfont;

	int width;
	int height;
	int posX;
	int posY;
};