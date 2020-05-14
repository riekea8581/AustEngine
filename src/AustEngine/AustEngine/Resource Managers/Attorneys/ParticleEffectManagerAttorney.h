#pragma once

#include "../ParticleEffectManager.h"

class ParticleEffectManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { ParticleEffectManager::Delete(); };
};