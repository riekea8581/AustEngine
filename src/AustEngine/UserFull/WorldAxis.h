#pragma once

#include "..\AustEngine\Game Object\GameObject.h"

class Model;
class ShaderObject;
class Texture;
class GraphicsObject_ColorNoTexture;

typedef GraphicsObject_ColorNoTexture Axis;

class WorldAxis : public Drawable
{
public:
	WorldAxis();
	~WorldAxis();

	virtual void Draw();

	Axis *getAxis() { return axis; };

private:
	Axis *axis;
};