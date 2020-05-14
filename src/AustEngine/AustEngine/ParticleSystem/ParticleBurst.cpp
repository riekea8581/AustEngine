#include "ParticleBurst.h"
#include "ParticleEmitter.h"
#include <stdlib.h> 
#include <time.h> 

void ParticleBurst::InitializeData(Vect pos, float range, float scale)
{
	myScale = scale;

	for (int i = 0; i < particleNum; i++)
	{
		particleArray[i].pos = pos;
		float rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * range - (range / 2);
		float ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * range - (range / 2);
		float rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * range - (range / 2);
		particleArray[i].dir = Vect(rx, ry, rz).getNorm();
		particleArray[i].dir[w] = 0;

		particleArray[i].speed = parent->GetStartSpeed();
	}
}

void ParticleBurst::DrawParticles(GraphicsObject * pGObj, Camera * pCam)
{
	for (int i = 0; i < particleNum; i++)
	{
		particleArray[i].pos += particleArray[i].dir * particleArray[i].speed;
		particleArray[i].speed -= parent->GetSpeedDec();
		if (particleArray[i].speed < 0) particleArray[i].speed = 0;

		Matrix Scale(SCALE, myScale, myScale, myScale);
		
		Vect right = Vect(0, 1, 0, 0).cross(particleArray[i].dir).getNorm();
		right[w] = 0;
		Vect up = particleArray[i].dir.cross(right).getNorm();
		up[w] = 0;

		Matrix RotZ;
		RotZ = Matrix(right, up, particleArray[i].dir, Vect(0, 0, 0));
		//RotZ = Matrix(ROT_Z, Vect(0, 1, 0).getAngle(particleArray[i].pos));
		
		Matrix Trans(TRANS, particleArray[i].pos.X(), particleArray[i].pos.Y(), particleArray[i].pos.Z());

		Matrix world = Scale * RotZ * Trans;
		pGObj->SetWorld(world);

		pGObj->Render(pCam);
	}
}