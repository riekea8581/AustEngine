#include "ParticleEmitterFactory.h"

ParticleEmitterFactory* ParticleEmitterFactory::ptrInstance = NULL;

ParticleEmitter * ParticleEmitterFactory::privCreateParticleEmitter(Vect v, ParticleEffect * effect)
{
	ParticleEmitter* p;
	if (recycledItems.empty())
	{
		p = new ParticleEmitter();
		allItems.push(p);
	}
	else
	{
		p = recycledItems.top();
		recycledItems.pop();
	}
	p->SetParent(effect);
	p->Initialize(v);
	return p;
}

void ParticleEmitterFactory::privRecycleParticleEmitter(ParticleEmitter* b)
{
	recycledItems.push(static_cast<ParticleEmitter*>(b));
}

void ParticleEmitterFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

ParticleEmitterFactory::~ParticleEmitterFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}