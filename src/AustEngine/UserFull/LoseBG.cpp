#include "LoseBG.h"
#include "..\AustEngine\AustEngine.h"
#include "..\AustEngine\Sprite\Sprite.h"
#include "..\AustEngine\Sprite\SpriteString.h"
#include "..\AustEngine\Resource Managers\SpriteFontManager.h"

LoseBG::LoseBG()
{
	mySprite = new Sprite("LoseBG");
	mySprite->SetPosition((float)AustEngine::GetWindowWidth() / 2, (float)AustEngine::GetWindowHeight() / 2);
	Drawable::SubmitSceneRegistration();
	line1 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press Enter to Restart", 100, 80);
	line2 = new SpriteString(SpriteFontManager::Get("GarfFont"), "Press Esc to Quit", 100, 30);
}

void LoseBG::Draw2D()
{
	mySprite->Render();
	line1->Render();
	line2->Render();
}

LoseBG::~LoseBG()
{
	Drawable::SubmitSceneDeregistration();
	delete mySprite;
	delete line1;
	delete line2;
}