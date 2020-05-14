#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "..\MathTools\MathTools.h"
#include "Commands\AABBCommandFactory.h"

void CollisionVolumeAABB::InitializeData(Model * mod, Matrix & mat)
{
	ComputeData(mod, mat);
}

void CollisionVolumeAABB::ComputeData(Model * mod, Matrix & mat)
{
	Vect *vList = mod->getVectList();
	Vect tmp = vList[0];
	tmp *= mat;
	float minX = tmp.X();
	float maxX = tmp.X();
	float minY = tmp.Y();
	float maxY = tmp.Y();
	float minZ = tmp.Z();
	float maxZ = tmp.Z();
	for (int i = 0; i < mod->getVectNum(); i++)
	{
		tmp = vList[i];
		tmp *= mat;
		if (tmp.X() < minX) minX = tmp.X();
		if (tmp.X() > maxX) maxX = tmp.X();
		if (tmp.Y() < minY) minY = tmp.Y();
		if (tmp.Y() > maxY) maxY = tmp.Y();
		if (tmp.Z() < minZ) minZ = tmp.Z();
		if (tmp.Z() > maxZ) maxZ = tmp.Z();
	}
	min = Vect(minX, minY, minZ);
	max = Vect(maxX, maxY, maxZ);
	trans = (max + min) * 0.5f;
	scale = max - min;

	World = mat;
	AdjWorld = (Matrix(SCALE, scale) * Matrix(TRANS, trans));

	float scaleMag = (Vect(1, 0, 0, 0) * mat).mag();
	Vect NewMax = (max - trans) * (1.0f / scaleMag);
	Vect NewMin = (min - trans) * (1.0f / scaleMag);

	HalfDiag = 0.5f * (NewMax - NewMin);
	HalfDiag[w] = 0;
	Center = (max + min) * 0.5f;

	ScaleSqr = (Vect(1, 0, 0, 0) * mat).magSqr();
}

void CollisionVolumeAABB::ComputeData(CollisionVolumeBSphere * s)
{
	float radius = s->GetRadius();
	min = Vect(s->GetCenter().X() - radius, s->GetCenter().Y() - radius, s->GetCenter().Z() - radius);
	max = Vect(s->GetCenter().X() + radius, s->GetCenter().Y() + radius, s->GetCenter().Z() + radius);
	trans = (max + min) * 0.5f;
	scale = max - min;

	World = Matrix(SCALE, s->GetRadius() * Vect(1, 1, 1)) * Matrix(TRANS, s->GetCenter());
	AdjWorld = (Matrix(SCALE, scale) * Matrix(TRANS, trans));

	float scaleMag = (Vect(1, 0, 0, 0) * World).mag();
	Vect NewMax = (max - trans) * (1.0f / scaleMag);
	Vect NewMin = (min - trans) * (1.0f / scaleMag);

	HalfDiag = 0.5f * (NewMax - NewMin);
	HalfDiag[w] = 0;
	Center = (max + min) * 0.5f;

	ScaleSqr = (Vect(1, 0, 0, 0) * World).magSqr();
}

void CollisionVolumeAABB::ComputeData(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	min = Vect(minX, minY, minZ);
	max = Vect(maxX, maxY, maxZ);
	trans = (max + min) * 0.5f;
	scale = max - min;

	World = (Matrix(SCALE, scale) * Matrix(TRANS, trans));
	AdjWorld = World;

	float scaleMag = (Vect(1, 0, 0, 0) * World).mag();
	Vect NewMax = (max - trans) * (1.0f / scaleMag);
	Vect NewMin = (min - trans) * (1.0f / scaleMag);

	HalfDiag = 0.5f * (NewMax - NewMin);
	HalfDiag[w] = 0;
	Center = (max + min) * 0.5f;

	ScaleSqr = (Vect(1, 0, 0, 0) * World).magSqr();
}

void CollisionVolumeAABB::SendColCommand(const Vect& col) const
{
	Visualizer::AddCommand(AABBCommandFactory::CreateCommand(*this, col));
};