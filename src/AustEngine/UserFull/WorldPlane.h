#pragma once

#include "..\AustEngine\Game Object\GameObject.h"

class Model;
class ShaderObject;
class Texture;
class GraphicsObject_TextureFlat;

typedef GraphicsObject_TextureFlat Plane;

class WorldPlane : public Drawable
{
public:
	WorldPlane();
	WorldPlane(const WorldPlane&) = delete;
	WorldPlane& operator=(const WorldPlane&) = delete;
	virtual ~WorldPlane();

	virtual void Draw();

	Plane *getPlane() { return plane; };

private:
	Plane *plane;
};