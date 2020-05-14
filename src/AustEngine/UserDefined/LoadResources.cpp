#include "AzulCore.h"
#include "..\AustEngine\AustEngine.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ImageManager.h"
#include "..\AustEngine\Resource Managers\SpriteFontManager.h"
#include "..\AustEngine\Resource Managers\ParticleEffectManager.h"
#include "..\AustEngine\ParticleSystem\ParticleEffect.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Resource Managers\ColorVectors.h"
#include "..\AustEngine\Scene\SceneManager.h"
#include "..\AustEngine\Terrain\TerrainObjectManager.h"
#include "..\UserFull\StartScene.h"

void AustEngine::LoadResources()
{
	// Default Loaded Models, DO NOT TOUCH
	ModelManager::LoadPremade("UnitSphere", Model::PreMadeModels::UnitSphere);
	ModelManager::LoadPremade("UnitBox", Model::PreMadeModels::UnitBox_WF);
	ModelManager::LoadPremade("UnitSquare2D", Model::PreMadeModels::UnitSquareXY);

	// Add your own resources here
	ModelManager::Load("Plane", "Plane.azul");
	ModelManager::Load("Tank", "Tank.azul");
	ModelManager::Load("Tree", "Tree.azul");

	ShaderManager::Load("textureFlatRender", "textureFlatRender");
	ShaderManager::Load("textureLightRender", "textureLightRender");
	ShaderManager::Load("colorConstantRender", "colorConstantRender");
	ShaderManager::Load("colorNoTextureRender", "colorNoTextureRender");
	ShaderManager::Load("spriteRender", "spriteRender");

	TextureManager::LoadPix("red", ColorVectors::Red);
	TextureManager::LoadPix("green", ColorVectors::Green);
	TextureManager::LoadPix("blue", ColorVectors::Blue);
	TextureManager::LoadPix("gray", ColorVectors::Gray);
	TextureManager::Load("Stage1Ground", "SandGround.tga");
	TextureManager::Load("Stage1Wall", "SandWall.tga");
	TextureManager::Load("Stage2Ground", "ForestGround.tga");
	TextureManager::Load("Stage2Wall", "ForestWall.tga");
	TextureManager::Load("Stage3Ground", "VolcanoGround.tga");
	TextureManager::Load("Stage3Wall", "VolcanoWall.tga");

	TextureManager::Load("StartBG", "Title.tga");
	TextureManager::Load("PauseBG", "Pause.tga"); 
	TextureManager::Load("LoseBG", "GameOver.tga");
	TextureManager::Load("WinBG", "Victory.tga");
	TextureManager::Load("redTank", "redTank.tga");
	TextureManager::Load("blueTank", "blueTank.tga");
	TextureManager::Load("redBar", "RedBar.tga");
	TextureManager::Load("Fireball", "Fireball.tga");
	TextureManager::Load("GarfFont", "Texture.tga");

	ImageManager::Load("StartBG", TextureManager::Get("StartBG"));
	ImageManager::Load("PauseBG", TextureManager::Get("PauseBG"));
	ImageManager::Load("LoseBG", TextureManager::Get("LoseBG"));
	ImageManager::Load("WinBG", TextureManager::Get("WinBG"));
	ImageManager::Load("redTank", TextureManager::Get("redTank"));
	ImageManager::Load("blueTank", TextureManager::Get("blueTank"));
	ImageManager::Load("redBar", TextureManager::Get("redBar"));
	ImageManager::Load("Fireball", TextureManager::Get("Fireball"));

	SpriteFontManager::Load("GarfFont", "GarfFont", "Metrics.xml");

	TerrainObjectManager::Load("Level0", "HeightMap0.tga", TextureManager::Get("Stage1Ground"), 1725, 64, 0, 1, 1);
	TerrainObjectManager::Load("Level1", "HeightMap1.tga", TextureManager::Get("Stage1Ground"), 1725, 64, 0, 1, 1);
	TerrainObjectManager::Load("Level2", "HeightMap2.tga", TextureManager::Get("Stage2Ground"), 1725, 64, 0, 1, 1);
	TerrainObjectManager::Load("Level3", "HeightMap3.tga", TextureManager::Get("Stage3Ground"), 1725, 64, 0, 1, 1);

	ParticleEffect * pe = new ParticleEffect();
	pe->SetGraphicsObject("UnitSquare2D", "Fireball");
	pe->SetBurstCount(10);
	pe->SetBurstFreq(1 / 20);
	pe->SetBurstLifespan(1);
	pe->SetEmitterLifespan(3);
	pe->SetParticleStartScale(5);
	pe->SetParticleVectRange(1);
	pe->SetStartSpeed(0.75f);
	pe->SetSpeedDec(0.015f);
	ParticleEffectManager::Load("FireExplosion", pe);

	SceneManager::SubmitChangeScene(new StartScene());
}