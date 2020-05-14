#pragma once

#include <map>
#include "AzulCore.h"

class ParticleEffect;

class ParticleEffectManager
{
	friend class ParticleEffectManagerAttorney;
private:
	static ParticleEffectManager* ptrInstance;

	ParticleEffectManager();
	ParticleEffectManager(const ParticleEffectManager&) = delete;
	ParticleEffectManager& operator=(const ParticleEffectManager&) = delete;
	~ParticleEffectManager() {};

	static ParticleEffectManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ParticleEffectManager;
		return *ptrInstance;
	}

	std::map < std::string, ParticleEffect * > map;
	std::map < std::string, ParticleEffect * >::iterator it;

	typedef std::pair< const char *, ParticleEffect * > Pair;

	void privLoad(const char *key, ParticleEffect * pe);
	ParticleEffect *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, ParticleEffect * pe) { Instance().privLoad(key, pe); };
	static ParticleEffect *Get(const char *key) { return Instance().privGet(key); };
};