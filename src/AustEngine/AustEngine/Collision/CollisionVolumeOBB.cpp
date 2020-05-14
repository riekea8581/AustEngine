#include "CollisionVolumeOBB.h"
#include "..\MathTools\MathTools.h"
#include "Commands\OBBCommandFactory.h"

void CollisionVolumeOBB::InitializeData(Model * mod, Matrix & mat)
{
	HalfDiag = Vect(0, 0, 0, 0);
	ComputeData(mod, mat);
	HalfDiag = 0.5f * (max - min);
	Center = (min + HalfDiag) * mat;
}

void CollisionVolumeOBB::ComputeData(Model * mod, Matrix & mat)
{
	min = mod->getMinAABB();
	max = mod->getMaxAABB();
	trans = (max + min) * 0.5f;
	scale = (max - min);

	World = mat;
	AdjWorld = (Matrix(SCALE, scale) * Matrix(TRANS, trans)) * mat;

	Center = (min + HalfDiag) * mat;
	ScaleSqr = (Vect(1, 0, 0, 0) * mat).mag() * (Vect(1, 0, 0, 0) * mat).mag();
}

void CollisionVolumeOBB::SendColCommand(const Vect& col) const
{
	Visualizer::AddCommand(OBBCommandFactory::CreateCommand(*this, col));
};