#include "StartBG.h"
#include "..\AustEngine\AustEngine.h"
#include "..\AustEngine\Sprite\Sprite.h"
#include "..\AustEngine\Sprite\SpriteString.h"
#include "..\AustEngine\Resource Managers\SpriteFontManager.h"

StartBG::StartBG()
{
	mySprite = new Sprite("StartBG");
	mySprite->SetPosition((float) AustEngine::GetWindowWidth() / 2, (float) AustEngine::GetWindowHeight() / 2);
	Drawable::SubmitSceneRegistration();
	line1 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press 1 to Start New Game", 100, 100);
	line2 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press 2 to Load Saved Game", 100, 50);
}

void StartBG::Draw2D()
{
	mySprite->Render();
	line1->Render();
	line2->Render();
}

StartBG::~StartBG()
{
	Drawable::SubmitSceneDeregistration();
	delete mySprite;
	delete line1;
	delete line2;
}