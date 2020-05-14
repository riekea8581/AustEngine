#pragma once

#include "..\AustEngine\Game Object\Drawable.h"

class SpriteString;

class LoseBG : public Drawable
{
public:
	LoseBG();
	LoseBG(const LoseBG&) = delete;
	LoseBG& operator=(const LoseBG&) = delete;
	virtual ~LoseBG();

	virtual void Draw2D();

private:
	Sprite * mySprite;
	SpriteString * line1;
	SpriteString * line2;
};