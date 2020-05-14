#pragma once

#include "..\AustEngine\Game Object\GameObject.h"

class Model;
class ShaderObject;
class Texture;
class GraphicsObject_TextureFlat;

typedef GraphicsObject_TextureFlat Plane;

class WallPlane : public Drawable
{
public:
	WallPlane() = delete;
	WallPlane(Matrix mat, Texture * tex);
	WallPlane(const WallPlane&) = delete;
	WallPlane& operator=(const WallPlane&) = delete;
	virtual ~WallPlane();

	virtual void Draw();

	Plane *getPlane() { return plane; };

private:
	Plane *plane;
};