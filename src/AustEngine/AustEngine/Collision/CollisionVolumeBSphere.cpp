#include "CollisionVolumeBSphere.h"
#include "..\MathTools\MathTools.h"
#include "Commands/BSphereCommandFactory.h"

void CollisionVolumeBSphere::ComputeData(Model * mod, Matrix & mat)
{
	center = mod->getCenter();
	radius = mod->getRadius();
	center *= mat;
	Vect scale = Vect(Vect(mat.M0(), mat.M4(), mat.M8())); // Assume Uniform Scaling, so check only one column
	radius *= scale.mag();
}

void CollisionVolumeBSphere::SendColCommand(const Vect& col) const
{
	Visualizer::AddCommand(BSphereCommandFactory::CreateCommand(*this, col));
};