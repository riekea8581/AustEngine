#include "PauseScene.h"
#include "UnpauseHack.h"
#include "PauseBG.h"

void PauseScene::Initialize()
{
	hack = new UnpauseHack();
	bg = new PauseBG();
}

void PauseScene::SceneEnd()
{
	delete hack;
	delete bg;
}