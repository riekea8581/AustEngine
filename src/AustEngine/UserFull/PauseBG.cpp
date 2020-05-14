#include "PauseBG.h"
#include "..\AustEngine\AustEngine.h"
#include "..\AustEngine\Sprite\Sprite.h"
#include "..\AustEngine\Sprite\SpriteString.h"
#include "..\AustEngine\Resource Managers\SpriteFontManager.h"

PauseBG::PauseBG()
{
	mySprite = new Sprite("PauseBG");
	mySprite->SetPosition((float)AustEngine::GetWindowWidth() / 2, (float)AustEngine::GetWindowHeight() / 2);
	Drawable::SubmitSceneRegistration();
	line1 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press Enter to Unpause", 100, 80);
	line2 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press Backspace to Export Save Game", 100, 30);
}

void PauseBG::Draw2D()
{
	mySprite->Render();
	line1->Render();
	line2->Render();
}

PauseBG::~PauseBG()
{
	Drawable::SubmitSceneDeregistration();
	delete mySprite;
	delete line1;
	delete line2;
}