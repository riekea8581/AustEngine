#include "ParticleEffectManager.h"
#include "../ParticleSystem/ParticleEffect.h"
#include "AzulCore.h"

ParticleEffectManager* ParticleEffectManager::ptrInstance = NULL;

ParticleEffectManager::ParticleEffectManager()
{

}

void ParticleEffectManager::privLoad(const char *key, ParticleEffect * pe)
{
	if (map.find(key) == map.end())
		map.insert(Pair(key, pe));
	else
		printf("Error: Key already in use");
}

ParticleEffect *ParticleEffectManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested particle effect");
	return nullptr;
}

void ParticleEffectManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, ParticleEffect * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}