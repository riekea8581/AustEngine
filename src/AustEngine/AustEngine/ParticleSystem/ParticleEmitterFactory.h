#pragma once

#include <stack>
#include "ParticleEmitter.h"

class ParticleEmitter;

class ParticleEmitterFactory
{
private:
	static ParticleEmitterFactory* ptrInstance;

	ParticleEmitterFactory() = default;
	ParticleEmitterFactory(const ParticleEmitterFactory&) = delete;
	ParticleEmitterFactory& operator=(const ParticleEmitterFactory&) = delete;
	~ParticleEmitterFactory();

	static ParticleEmitterFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ParticleEmitterFactory;
		return *ptrInstance;
	}

	std::stack<ParticleEmitter*> allItems;
	std::stack<ParticleEmitter*> recycledItems;

	ParticleEmitter * privCreateParticleEmitter(Vect v, ParticleEffect * effect);
	void privRecycleParticleEmitter(ParticleEmitter* p);

public:

	static ParticleEmitter * CreateParticleEmitter(Vect v, ParticleEffect * effect) { return Instance().privCreateParticleEmitter(v, effect); };
	static void RecycleParticleEmitter(ParticleEmitter* p) { Instance().privRecycleParticleEmitter(p); };
	static void Terminate();
};