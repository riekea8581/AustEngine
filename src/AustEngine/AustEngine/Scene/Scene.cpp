#include "Scene.h"
#include "../Collision/Visualizer.h"

void Scene::Update()
{
	broker.ExecuteCommands();
	alarmMgr.ProcessElements();
	updateMgr.ProcessElements();
	keyboardMgr.ProcessEvents();
	collideMgr.ProcessCollisions();
}

void Scene::Draw()
{
	terrainMgr.DrawTerrain();
	drawMgr.ProcessElements();
	VisualizerAttorney::VizDisplay::VisualizeAll();
}

Camera * Scene::getCamera()
{
	return camMgr.getCamera();
}

Camera * Scene::getOrthCamera()
{
	return camMgr.getOrthCamera();
}

TerrainObject * Scene::getTerrain()
{
	return terrainMgr.getTerrain();
}

void Scene::setTerrain(const char * tag)
{
	terrainMgr.setTerrain(tag);
}