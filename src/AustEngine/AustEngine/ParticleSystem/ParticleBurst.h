#pragma once

#include "Particle.h"

class ParticleEmitter;

class ParticleBurst : public Align16
{
public:
	ParticleBurst() {};
	ParticleBurst(const ParticleBurst&) = delete;
	ParticleBurst& operator=(const ParticleBurst&) = delete;
	virtual ~ParticleBurst() {};

	void InitializeData(Vect pos, float range, float scale);
	void DrawParticles(GraphicsObject * pGObj, Camera * pCam);

	void SetParent(ParticleEmitter * effect) { parent = effect; };

private:
	static const int particleNum = 5;

	Particle particleArray[particleNum];
	float myScale;

	ParticleEmitter * parent;
};