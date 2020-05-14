#include "AzulCore.h"
#include "AustEngine.h"
#include "Resource Managers\ShaderManager.h"
#include "Resource Managers\TextureManager.h"
#include "Resource Managers\ModelManager.h"
#include "Resource Managers\Attorneys\ShaderManagerAttorney.h"
#include "Resource Managers\Attorneys\TextureManagerAttorney.h"
#include "Resource Managers\Attorneys\ModelManagerAttorney.h"
#include "Resource Managers\Attorneys\ImageManagerAttorney.h"
#include "Resource Managers\Attorneys\SpriteFontManagerAttorney.h"
#include "Resource Managers\Attorneys\ParticleEffectManagerAttorney.h"
#include "Terrain\TerrainObjectManagerAttorney.h"
#include "Camera Manager\CameraManager.h"
#include "Scene\SceneManagerAttorney.h"
#include "Scene\SceneAttorney.h"
#include "Time Manager\TimeAttorney.h"

AustEngine* AustEngine::ptrInstance = NULL;

//-----------------------------------------------------------------------------
// AustEngine::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void AustEngine::Initialize()
{
	this->AustInitialize();
}

//-----------------------------------------------------------------------------
// AustEngine::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void AustEngine::LoadContent()
{
	this->LoadResources();

	SceneManagerAttorney::SceneManagement::InitStartScene();
}

//-----------------------------------------------------------------------------
// AustEngine::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void AustEngine::Update()
{
	TimeAttorney::CalculateTime();
	SceneManagerAttorney::SceneManagement::Update();
}

//-----------------------------------------------------------------------------
// AustEngine::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void AustEngine::Draw()
{
	SceneManagerAttorney::SceneManagement::Draw();
}



//-----------------------------------------------------------------------------
// AustEngine::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void AustEngine::UnLoadContent()
{
	this->AustEnd();

	SceneAttorney::SceneGameLoop::SceneEnd(SceneManager::GetCurrentScene());
	SceneManagerAttorney::SceneManagement::Delete();
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();
	ParticleEffectManagerAttorney::Delete();
	TerrainObjectManagerAttorney::Delete();
	TimeAttorney::Delete();
	VisualizerAttorney::VizDelete::Delete();
	StorableManager::Terminate();
}