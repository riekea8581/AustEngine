#include "MathTools.h"
#include "..\Collision\CollisionVolumeBSphere.h"
#include "..\Collision\CollisionVolumeBox.h"
#include "..\Collision\CollisionVolumeAABB.h"
#include "..\Collision\CollisionVolumeOBB.h"
#include "..\Collision\Attorneys\BoxAttorney.h"

bool MathTools::Intersect(const CollisionVolume & A, const CollisionVolume & B)
{
	return A.IntersectAccept(B);
}

bool MathTools::Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeBSphere & B)
{
	Vect dist = A.GetCenter() - B.GetCenter();
	return (dist.mag() <= A.GetRadius() + B.GetRadius());
}

bool MathTools::Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeAABB & B)
{
	Vect clampedCenter = ClampPoint(A.GetCenter(), B.GetMin(), B.GetMax());
	return ((A.GetCenter() - clampedCenter).mag() <= A.GetRadius());
}

bool MathTools::Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeOBB & B)
{
	Vect invCenter = A.GetCenter() * BoxAttorney::GetWorld(B).getInv();
	Vect clampedCenter = ClampPoint(invCenter, B.GetMin(), B.GetMax());
	Vect worldCenter = clampedCenter * BoxAttorney::GetWorld(B);
	Vect dist = A.GetCenter() - worldCenter;
	return (dist.mag() <= A.GetRadius());
}

bool MathTools::Intersect(const CollisionVolumeAABB & A, const CollisionVolumeAABB & B)
{
	return (TestIntervalOverlap(A.GetMin().X(), A.GetMax().X(), B.GetMin().X(), B.GetMax().X()) &&
			TestIntervalOverlap(A.GetMin().Y(), A.GetMax().Y(), B.GetMin().Y(), B.GetMax().Y()) &&
			TestIntervalOverlap(A.GetMin().Z(), A.GetMax().Z(), B.GetMin().Z(), B.GetMax().Z()));
}

bool MathTools::Intersect(const CollisionVolumeAABB & A, const CollisionVolumeOBB & B)
{
	Vect AFaceX = BoxAttorney::GetWorld(A).get(ROW_0);
	Vect AFaceY = BoxAttorney::GetWorld(A).get(ROW_1);
	Vect AFaceZ = BoxAttorney::GetWorld(A).get(ROW_2);
	Vect BFaceX = BoxAttorney::GetWorld(B).get(ROW_0);
	Vect BFaceY = BoxAttorney::GetWorld(B).get(ROW_1);
	Vect BFaceZ = BoxAttorney::GetWorld(B).get(ROW_2);
	Vect CrossXX = AFaceX.cross(BFaceX);
	Vect CrossXY = AFaceX.cross(BFaceY);
	Vect CrossXZ = AFaceX.cross(BFaceZ);
	Vect CrossYX = AFaceY.cross(BFaceX);
	Vect CrossYY = AFaceY.cross(BFaceY);
	Vect CrossYZ = AFaceY.cross(BFaceZ);
	Vect CrossZX = AFaceZ.cross(BFaceX);
	Vect CrossZY = AFaceZ.cross(BFaceY);
	Vect CrossZZ = AFaceZ.cross(BFaceZ);
	return !(!SATCheck(AFaceX, A, B) || !SATCheck(AFaceY, A, B) || !SATCheck(AFaceZ, A, B) || !SATCheck(BFaceX, A, B)
		|| !SATCheck(BFaceY, A, B) || !SATCheck(BFaceZ, A, B) || !SATCheck(CrossXX, A, B) || !SATCheck(CrossXY, A, B)
		|| !SATCheck(CrossXZ, A, B) || !SATCheck(CrossYX, A, B) || !SATCheck(CrossYY, A, B) || !SATCheck(CrossYZ, A, B)
		|| !SATCheck(CrossZX, A, B) || !SATCheck(CrossZY, A, B) || !SATCheck(CrossZZ, A, B));
}

bool MathTools::Intersect(const CollisionVolumeOBB & A, const CollisionVolumeOBB & B)
{
	Vect AFaceX = BoxAttorney::GetWorld(A).get(ROW_0);
	Vect AFaceY = BoxAttorney::GetWorld(A).get(ROW_1);
	Vect AFaceZ = BoxAttorney::GetWorld(A).get(ROW_2);
	Vect BFaceX = BoxAttorney::GetWorld(B).get(ROW_0);
	Vect BFaceY = BoxAttorney::GetWorld(B).get(ROW_1);
	Vect BFaceZ = BoxAttorney::GetWorld(B).get(ROW_2);
	Vect CrossXX = AFaceX.cross(BFaceX);
	Vect CrossXY = AFaceX.cross(BFaceY);
	Vect CrossXZ = AFaceX.cross(BFaceZ);
	Vect CrossYX = AFaceY.cross(BFaceX);
	Vect CrossYY = AFaceY.cross(BFaceY);
	Vect CrossYZ = AFaceY.cross(BFaceZ);
	Vect CrossZX = AFaceZ.cross(BFaceX);
	Vect CrossZY = AFaceZ.cross(BFaceY);
	Vect CrossZZ = AFaceZ.cross(BFaceZ);
	return !(!SATCheck(AFaceX, A, B) || !SATCheck(AFaceY, A, B) || !SATCheck(AFaceZ, A, B) || !SATCheck(BFaceX, A, B)
		|| !SATCheck(BFaceY, A, B) || !SATCheck(BFaceZ, A, B) || !SATCheck(CrossXX, A, B) || !SATCheck(CrossXY, A, B)
		|| !SATCheck(CrossXZ, A, B) || !SATCheck(CrossYX, A, B) || !SATCheck(CrossYY, A, B) || !SATCheck(CrossYZ, A, B)
		|| !SATCheck(CrossZX, A, B) || !SATCheck(CrossZY, A, B) || !SATCheck(CrossZZ, A, B));
}

bool MathTools::Intersect(const Vect & A, const CollisionVolumeAABB & B)
{
	return (A.X() >= B.GetMin().X() && A.X() <= B.GetMax().X() &&
			A.Y() >= B.GetMin().Y() && A.Y() <= B.GetMax().Y() && 
			A.Z() >= B.GetMin().Z() && A.Z() <= B.GetMax().Z());
}

bool MathTools::Intersect(const Vect & A, const CollisionVolumeOBB & B)
{
	Vect invA = A * BoxAttorney::GetWorld(B).getInv();
	return (invA.X() > B.GetMin().X() && invA.X() < B.GetMax().X() &&
		invA.Y() > B.GetMin().Y() && invA.Y() < B.GetMax().Y() &&
		invA.Z() > B.GetMin().Z() && invA.Z() < B.GetMax().Z());
}

float MathTools::Clamp(float target, float min, float max)
{
	if (target < min) return min;
	if (target > max) return max;
	return target;
}

Vect MathTools::ClampPoint(Vect target, Vect min, Vect max)
{
	return Vect(Clamp(target.X(), min.X(), max.X()), Clamp(target.Y(), min.Y(), max.Y()), 
				Clamp(target.Z(), min.Z(), max.Z()));
}

bool MathTools::TestIntervalOverlap(float minA, float maxA, float minB, float maxB)
{
	return !(maxA < minB || maxB < minA);
}

bool MathTools::SATCheck(Vect v, const CollisionVolumeBox & A, const CollisionVolumeBox & B)
{
	if (v.magSqr() > FLT_EPSILON)
	{
		Vect CenterDiff = B.GetCenter() - A.GetCenter();
		float D = abs(CenterDiff.dot(v)) / v.mag();
		float projA = ProjMax(v, A, BoxAttorney::GetWorld(A).getInv());
		float projB = ProjMax(v, B, BoxAttorney::GetWorld(B).getInv());
		return D <= projA + projB;
	}
	return true;
}

float MathTools::ProjMax(Vect v, const CollisionVolumeBox & A, const Matrix & invMat)
{
	Vect invVect = v * invMat;
	float projX = abs(invVect.X() * A.GetHalfDiag().X());
	float projY = abs(invVect.Y() * A.GetHalfDiag().Y());
	float projZ = abs(invVect.Z() * A.GetHalfDiag().Z());
	return (projX + projY + projZ) / v.mag() * A.GetScaleSqr();
}