#pragma once

#include "AzulCore.h"

class ParticleEffect
{
public:
	ParticleEffect() {};
	ParticleEffect(const ParticleEffect&) = delete;
	ParticleEffect& operator=(const ParticleEffect&) = delete;
	virtual ~ParticleEffect() { delete particleObj; };

	void SpawnParticleGenerator(Vect v);

	GraphicsObject * getGraphicsObject() { return particleObj; };
	float GetEmitterLifespan() { return EmitterLifespan; };
	float GetBurstLifespan() { return BurstLifespan; };
	float GetBurstFreq() { return BurstFrequency; };
	float GetParticleStartScale() { return ParticleStartScale; };
	float GetParticleVectRange() { return ParticleVectRange; };
	int GetBurstCount() { return BurstCount; };
	float GetStartSpeed() { return StartSpeed; };
	float GetSpeedDec() { return SpeedDec; };

	void SetGraphicsObject(char * modTag, char * texTag);
	void SetEmitterLifespan(float eLife) { EmitterLifespan = eLife; };
	void SetBurstLifespan(float bLife) { BurstLifespan = bLife; };
	void SetBurstFreq(float f) { BurstFrequency = f; };
	void SetParticleStartScale(float scale) { ParticleStartScale = scale; };
	void SetParticleVectRange(float range) { ParticleVectRange = range; };
	void SetBurstCount(int count) { BurstCount = count; };
	void SetStartSpeed(float speed) { StartSpeed = speed; };
	void SetSpeedDec(float dec) { SpeedDec = dec; };

private:
	GraphicsObject * particleObj;
	float EmitterLifespan;
	float BurstLifespan;
	float BurstFrequency;
	float ParticleStartScale;
	float ParticleVectRange;
	int BurstCount;
	float StartSpeed;
	float SpeedDec;
};