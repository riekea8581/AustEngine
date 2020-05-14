#pragma once

#include "..\Game Object\GameObject.h"

class Model;
class ShaderObject;
class Texture;
class GraphicsObject_TextureFlat;

typedef GraphicsObject_TextureFlat Terrain;

struct MinMaxData : public Align16
{
	Vect min;
	Vect max;
	Vect BottomLeft;
	Vect BottomRight;
	Vect TopLeft;
	Vect TopRight;
};

class TerrainObject : public Drawable
{

private:
	float length;
	size_t side;
	size_t pixel_width;
	Terrain * pModTerrain;
	MinMaxData * MinMaxList;

	int TexelIndex(int side, int i, int j) const;

public:
	TerrainObject() = delete;							// Default constructor
	TerrainObject(const TerrainObject&) = delete;				// Copy constructor
	TerrainObject(Model&&) = delete;						// Move constructor
	TerrainObject& operator=(const TerrainObject&) & = delete;  // Copy assignment operator
	TerrainObject& operator=(TerrainObject&&) & = delete;       // Move assignment operator
	~TerrainObject();

	TerrainObject(const char * heightmapFile, Texture * tex, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	virtual void Draw();

	int HighlightCell(const Vect & v) const;
	Vect SnapToCell(const Vect & v);
	Vect GetFaceNormal(const Vect & v);
	void HighlightAllCells(const CollisionVolume & a, const CollisionVolumeBSphere & b, const Vect & min, const Vect & max);
	CollisionVolumeAABB getAABB(int start, int x, int y) const;
	int getXLen(int min, int max) const;
	int getZLen(int min, int max) const;
};