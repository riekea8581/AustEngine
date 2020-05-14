#pragma once

#include "..\AustEngine\Game Object\Drawable.h"

class SpriteString;

class StartBG : public Drawable
{
public:
	StartBG();
	StartBG(const StartBG&) = delete;
	StartBG& operator=(const StartBG&) = delete;
	virtual ~StartBG();

	virtual void Draw2D();

private:
	Sprite * mySprite;
	SpriteString * line1;
	SpriteString * line2;
};