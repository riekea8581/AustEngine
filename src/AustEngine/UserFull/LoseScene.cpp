#include "LoseScene.h"
#include "RestartHack.h"
#include "LoseBG.h"

void LoseScene::Initialize()
{
	hack = new RestartHack();
	bg = new LoseBG();
}

void LoseScene::SceneEnd()
{
	delete hack;
	delete bg;
}