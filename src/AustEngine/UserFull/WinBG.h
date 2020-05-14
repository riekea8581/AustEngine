#pragma once

#include "..\AustEngine\Game Object\Drawable.h"

class SpriteString;

class WinBG : public Drawable
{
public:
	WinBG();
	WinBG(const WinBG&) = delete;
	WinBG& operator=(const WinBG&) = delete;
	virtual ~WinBG();

	virtual void Draw2D();

private:
	Sprite * mySprite;
	SpriteString * line1;
	SpriteString * line2;
}; 