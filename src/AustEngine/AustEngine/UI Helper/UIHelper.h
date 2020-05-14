#pragma once

#include "AzulCore.h"

class Sprite;

class UIHelper
{
public:
	/// \brief A function that, given a sprite, count, and position info, will draw a
	/// health bar on-screen.
	/// 
	/// \ingroup UIEVENTS
	/// 
	/// This function provides the user with an easily-accessible health bar interface.
	/// The function takes the following inputs: a sprite to draw; and X & Y position to
	/// start drawing at; an X offset between each sprite drawn; and a count of how many
	/// sprites to draw. Then, a row of this sprite will be drawn. To get the "classic"
	/// health bar look, a square sprite can be used with a small X offset to give the
	/// appearance of a solid bar. Note that this function must be called from the
	/// calling object's Draw2D function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an Enemy Manager drawing the number of remaining
	/// enemies through the health bar interface, at position (100, 100) with an offset
	/// of 50 between sprites.
	///
	/// \code
	/// 
	/// void EnemyManager::Draw2D()
	/// {
	///		DrawHealthBar(EnemySprite, 100, 100, 50, EnemyCount);
	/// }
	/// \endcode
	static void DrawHealthBar(Sprite * s, float xPos, float yPos, float xTrans, int count);
};