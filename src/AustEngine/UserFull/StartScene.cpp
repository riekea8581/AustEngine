#include "StartScene.h"
#include "StartHack.h"
#include "StartBG.h"

void StartScene::Initialize()
{
	hack = new StartHack();
	bg = new StartBG();
}

void StartScene::SceneEnd()
{
	delete hack;
	delete bg;
}