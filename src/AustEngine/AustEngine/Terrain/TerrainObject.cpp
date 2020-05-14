#include "TerrainObject.h"
#include "AzulCore.h"
#include "TextureTGA.h"
#include "GpuVertTypes.h"
#include "..\Resource Managers\ShaderManager.h"
#include "..\Resource Managers\TextureManager.h"
#include "..\Resource Managers\ModelManager.h"
#include "..\Camera Manager\CameraManager.h"
#include "..\Scene\SceneManager.h"
#include "..\MathTools\MathTools.h"
#include "..\Collision\CollisionVolumeBSphere.h"
#include "..\Collision\CollisionVolumeAABB.h"
#include "..\Collision\Attorneys\AABBAttorney.h"
#include "..\Game Object\Attorneys\CollisionAttorney.h"


TerrainObject::TerrainObject(const char * heightmapFile, Texture * tex, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	length = len;
	int imgWidth, imgHeigth, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert(imgWidth == imgHeigth && imgWidth != 0);

	side = imgWidth;	// the image should be square
	pixel_width = 3;			// 4 bytes RGBA per pixel

	int nverts = (int)side * (int)side;
	VertexStride_VUN * pVerts = new VertexStride_VUN[nverts];

	int ntri = (int)(side - 1) * (int)(side - 1) * 2;
	TriangleIndex * pTriList = new TriangleIndex[ntri];
	MinMaxList = new MinMaxData[ntri / 2];

	float xPos = -len / 2 + len / side / 2;
	float yPos = 0;
	float zPos = -len / 2 + len / side / 2;
	float uPos = 0;
	float vPos = 0;

	// Generate Vertices
	for (int i = 0; i < (int)side; i++)
	{
		for (int j = 0; j < (int)side; j++)
		{
			yPos = static_cast<unsigned char>(imgData[TexelIndex(side, i, side - 1 - j)]) / 255.0f * maxheight + ytrans;
			int index = i * side + j;
			pVerts[index].set(xPos, yPos, zPos, uPos, vPos, 0, 0, 0);
			xPos += len / side;
			uPos += (float)RepeatU / side;

		}
		xPos = -len / 2 + len / side / 2;
		uPos = 0;
		zPos += len / side;
		vPos += (float)RepeatV / side;
	}

	// Generate Normals
	float faceCount = 0;
	Vect face1 = Vect(0, 0, 0);
	Vect face2 = Vect(0, 0, 0);
	Vect face3 = Vect(0, 0, 0);
	Vect face4 = Vect(0, 0, 0);
	Vect face5 = Vect(0, 0, 0);
	Vect face6 = Vect(0, 0, 0);
	for (int i = 0; i < nverts; i++)
	{
		if (i - (int)side >= 0)
		{
			if (i % side > 0)
			{
				faceCount++;
				face1 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i - 1].x, pVerts[i - 1].y, pVerts[i - 1].z))
					.cross(Vect(pVerts[i - side].x, pVerts[i - side].y, pVerts[i - side].z) - Vect(pVerts[i - 1].x, pVerts[i - 1].y, pVerts[i - 1].z));
			}
			if (i % side < 15)
			{
				faceCount += 2;
				face2 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i + 1].x, pVerts[i + 1].y, pVerts[i + 1].z))
					.cross(Vect(pVerts[i - side + 1].x, pVerts[i - side + 1].y, pVerts[i - side + 1].z) - Vect(pVerts[i + 1].x, pVerts[i + 1].y, pVerts[i + 1].z));
				face3 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i - side].x, pVerts[i - side].y, pVerts[i - side].z))
					.cross(Vect(pVerts[i - side + 1].x, pVerts[i - side + 1].y, pVerts[i - side + 1].z) - Vect(pVerts[i - side].x, pVerts[i - side].y, pVerts[i - side].z));
			}
		}
		if (i < nverts - (int)side)
		{
			if (i % side > 0)
			{
				faceCount += 2;
				face4 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i - 1].x, pVerts[i - 1].y, pVerts[i - 1].z))
					.cross(Vect(pVerts[i + side - 1].x, pVerts[i + side - 1].y, pVerts[i + side - 1].z) - Vect(pVerts[i - 1].x, pVerts[i - 1].y, pVerts[i - 1].z));
				face5 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i + 1].x, pVerts[i + 1].y, pVerts[i + 1].z))
					.cross(Vect(pVerts[i + side - 1].x, pVerts[i + side - 1].y, pVerts[i + side - 1].z) - Vect(pVerts[i + 1].x, pVerts[i + 1].y, pVerts[i + 1].z));
			}
			if (i % side < 15)
			{
				faceCount++;
				face6 = (Vect(pVerts[i].x, pVerts[i].y, pVerts[i].z) - Vect(pVerts[i + side].x, pVerts[i + side].y, pVerts[i + side].z))
					.cross(Vect(pVerts[i + 1].x, pVerts[i + 1].y, pVerts[i + 1].z) - Vect(pVerts[i + side].x, pVerts[i + side].y, pVerts[i + side].z));
			}
		}
		Vect normal = (face1 + face2 + face3 + face4 + face5 + face6) * (1.0f / faceCount);
		pVerts[i].nx = normal.X();
		pVerts[i].ny = normal.Y();
		pVerts[i].nz = normal.Z();
		faceCount = 0;
		face1 = Vect(0, 0, 0);
		face2 = Vect(0, 0, 0);
		face3 = Vect(0, 0, 0);
		face4 = Vect(0, 0, 0);
		face5 = Vect(0, 0, 0);
		face6 = Vect(0, 0, 0);
	}

	// Generate Tris
	int index = 0;
	for (int i = 0; i < ntri; i++)
	{
		pTriList[i].set(index, index + side + 1, index + 1);
		i++;
		pTriList[i].set(index, index + side, index + side + 1);
		index++;
		if (index % (side) == side - 1)
			index++;
	}

	// Generate AABBs
	index = 0;
	for (int i = 0; i < ntri / 2; i++)
	{
		float minY = pVerts[index].y;
		if (pVerts[index + 1].y < minY) minY = pVerts[index + 1].y;
		if (pVerts[index + side].y < minY) minY = pVerts[index + side].y;
		if (pVerts[index + side + 1].y < minY) minY = pVerts[index + side + 1].y;

		float maxY = pVerts[index].y;
		if (pVerts[index + 1].y > maxY) maxY = pVerts[index + 1].y;
		if (pVerts[index + side].y > maxY) maxY = pVerts[index + side].y;
		if (pVerts[index + side + 1].y > maxY) maxY = pVerts[index + side + 1].y;

		MinMaxList[i].min = Vect(pVerts[index].x, minY, pVerts[index].z);
		MinMaxList[i].max = Vect(pVerts[index + side + 1].x, maxY, pVerts[index + side + 1].z);
		MinMaxList[i].TopLeft = Vect(pVerts[index].x, pVerts[index].y, pVerts[index].z);
		MinMaxList[i].TopRight = Vect(pVerts[index + side].x, pVerts[index + side].y, pVerts[index + side].z);
		MinMaxList[i].BottomLeft = Vect(pVerts[index + 1].x, pVerts[index + 1].y, pVerts[index + 1].z);
		MinMaxList[i].BottomRight = Vect(pVerts[index + side + 1].x, pVerts[index + side + 1].y, pVerts[index + side + 1].z);
		index++;
		if (index % (side) == side - 1)
			index++;
	}

	Model *pModelTerrain = new Model(pVerts, nverts, pTriList, ntri);
	Texture *pTextTerrain = tex;
	ShaderObject *pShaderObject_texture = ShaderManager::Get("textureFlatRender");
	pModTerrain = new Terrain(pModelTerrain, pShaderObject_texture, pTextTerrain);
	Matrix world = Matrix(IDENTITY);
	pModTerrain->SetWorld(world);

	delete[] pVerts;
	delete[] pTriList;

	Drawable::SubmitSceneRegistration(); 
}

int TerrainObject::TexelIndex(int s, int i, int j) const
{
	return pixel_width * (j * s + i);
}

void TerrainObject::Draw()
{
	pModTerrain->Render(SceneManager::GetCurrentScene()->getCamera());
	//for (int i = 0; i < pModTerrain->getModel()->getTriNum() / 2; i++)
	//{
	//	//VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[i].min, MinMaxList[i].max, Vect(0, 1.0f, 0));
	//}
}

int TerrainObject::HighlightCell(const Vect & v) const
{
	float targetX = v.X() + length / 2;
	float targetZ = v.Z() + length / 2;
	int targetCell = 0;
	while (targetX - (length / side) > length / side / 2)
	{
		targetX -= (length / side);
		targetCell++;
	}
	while (targetZ - (length / side) > length / side / 2)
	{
		targetZ -= (length / side);
		targetCell += side - 1;
	}
	//VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[targetCell].min, MinMaxList[targetCell].max, Vect(0, 1.0f, 0));
	return targetCell;
}

Vect TerrainObject::SnapToCell(const Vect & v)
{
	float targetX = v.X() + length / 2;
	float targetZ = v.Z() + length / 2;
	int targetCell = 0;
	while (targetX - (length / side) > length / side / 2)
	{
		targetX -= (length / side);
		targetCell++;
	}
	while (targetZ - (length / side) > length / side / 2)
	{
		targetZ -= (length / side);
		targetCell += side - 1;
	}
	return Vect(v.X(), (MinMaxList[targetCell].max.Y() + MinMaxList[targetCell].min.Y()) / 2, v.Z());
}

Vect TerrainObject::GetFaceNormal(const Vect & v)
{
	float targetX = v.X() + length / 2;
	float targetZ = v.Z() + length / 2;
	int targetCell = 0;
	while (targetX - (length / side) > length / side / 2)
	{
		targetX -= (length / side);
		targetCell++;
	}
	while (targetZ - (length / side) > length / side / 2)
	{
		targetZ -= (length / side);
		targetCell += side - 1;
	}
	//VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[targetCell].min, MinMaxList[targetCell].max, Vect(0, 1.0f, 0));
	Vect max = MinMaxList[targetCell].TopLeft;
	Vect min = MinMaxList[targetCell].BottomRight;
	Vect tmp;
	if (targetX < targetZ)
	{
		tmp = MinMaxList[targetCell].TopRight;
		max = max - tmp;
		max[w] = 0;
		min = min - tmp;
		min[w] = 0;
		tmp = min.cross(max);
		tmp = tmp.getNorm();
		tmp[w] = 0;
		return tmp;
	}
	else
	{
		tmp = MinMaxList[targetCell].BottomLeft;
		max = max - tmp;
		max[w] = 0;
		min = min - tmp;
		min[w] = 0;
		tmp = max.cross(min);
		tmp = tmp.getNorm();
		tmp[w] = 0;
		return tmp;
	}

}

void TerrainObject::HighlightAllCells(const CollisionVolume & a, const CollisionVolumeBSphere & b, const Vect & min, const Vect & max)
{
	int minCell = HighlightCell(min);
	int maxCell = HighlightCell(max);
	int xOffset = minCell % (side - 1) - maxCell % (side - 1);
	int zOffset = minCell / (side - 1) - maxCell / (side - 1);
	for (int i = 0; i <= xOffset; i++)
	{
		for (int j = 0; j <= zOffset; j++)
		{
			int targetCell = maxCell + i + (side - 1) * j;
			VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[targetCell].min, MinMaxList[targetCell].max, Vect(0, 1.0f, 0));
			CollisionVolumeAABB tmp;
			AABBAttorney::ComputeData(&tmp, MinMaxList[targetCell].min.X(), MinMaxList[targetCell].min.Y(), MinMaxList[targetCell].min.Z(),
				MinMaxList[targetCell].max.X(), MinMaxList[targetCell].max.Y(), MinMaxList[targetCell].max.Z());
			if (MathTools::Intersect(b, tmp))
			{
				VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[targetCell].min, MinMaxList[targetCell].max, Vect(1.0f, 1.0f, 0));
				if (MathTools::Intersect(a, tmp))
				{
					VisualizerAttorney::VizDisplay::ShowAABB(MinMaxList[targetCell].min, MinMaxList[targetCell].max, Vect(1.0f, 0, 0));
				}
			}
		}
	}
}

CollisionVolumeAABB TerrainObject::getAABB(int start, int x, int y) const
{
	int targetCell = start + x + (side - 1) * y;
	CollisionVolumeAABB tmp;
	if(targetCell > (int)(side - 1) * (int)(side - 1))
		AABBAttorney::ComputeData(&tmp, 0, 0, 0, 0, 0, 0);
	else AABBAttorney::ComputeData(&tmp, MinMaxList[targetCell].min.X(), MinMaxList[targetCell].min.Y(), MinMaxList[targetCell].min.Z(),
		MinMaxList[targetCell].max.X(), MinMaxList[targetCell].max.Y(), MinMaxList[targetCell].max.Z());
	return tmp;
}

int TerrainObject::getXLen(int min, int max) const
{
	return min % (side - 1) - max % (side - 1);
}

int TerrainObject::getZLen(int min, int max) const
{
	return min / (side - 1) - max / (side - 1);
}


TerrainObject::~TerrainObject()
{
	delete pModTerrain->getModel();
	delete pModTerrain;
	delete[] MinMaxList;
}