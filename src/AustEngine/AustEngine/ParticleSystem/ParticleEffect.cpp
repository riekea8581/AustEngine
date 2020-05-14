#include "ParticleEffect.h"
#include "ParticleEmitterFactory.h"
#include "..\Resource Managers\ShaderManager.h"
#include "..\Resource Managers\TextureManager.h"
#include "..\Resource Managers\ModelManager.h"

void ParticleEffect::SpawnParticleGenerator(Vect v)
{
	ParticleEmitterFactory::CreateParticleEmitter(v, this);
}

void ParticleEffect::SetGraphicsObject(char * modTag, char * texTag)
{
	Model *pModelSprite = ModelManager::Get(modTag);
	ShaderObject *pShaderObject_sprite = ShaderManager::Get("textureFlatRender");
	Texture *pTexSprite = TextureManager::Get(texTag);
	particleObj = new GraphicsObject_TextureFlat(pModelSprite, pShaderObject_sprite, pTexSprite);
}