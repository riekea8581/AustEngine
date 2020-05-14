#pragma once

#include "..\AustEngine\Game Object\Drawable.h"

class SpriteString;

class PauseBG : public Drawable
{
public:
	PauseBG();
	PauseBG(const PauseBG&) = delete;
	PauseBG& operator=(const PauseBG&) = delete;
	virtual ~PauseBG();

	virtual void Draw2D();

private:
	Sprite * mySprite;
	SpriteString * line1;
	SpriteString * line2;
};