#include "WinScene.h"
#include "RestartHack.h"
#include "WinBG.h"

void WinScene::Initialize()
{
	hack = new RestartHack();
	bg = new WinBG();
}

void WinScene::SceneEnd()
{
	delete hack;
	delete bg;
}