#include "Visualizer.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "Attorneys\VolumeAttorney.h"
#include "Attorneys\BoxAttorney.h"
#include "Commands\BSphereColCommand.h"
#include "Commands\AABBColCommand.h"
#include "Commands\OBBColCommand.h"
#include "Commands\BSphereCommandFactory.h"
#include "Commands\AABBCommandFactory.h"
#include "Commands\OBBCommandFactory.h"
#include "..\Resource Managers\ModelManager.h"
#include "..\Resource Managers\ShaderManager.h"
#include "..\Scene\SceneManager.h"

Visualizer * Visualizer::ptrInstance = NULL;

Visualizer::Visualizer()
{
	Model *PModelSphere = ModelManager::Get("UnitSphere");
	Model *PModelBox = ModelManager::Get("UnitBox"); 
	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("colorConstantRender");
	Vect Default(0.0f, 0.0f, 0.0f, 1.0f);
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(PModelSphere, pShaderObject_constantColor, Default);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(PModelBox, pShaderObject_constantColor, Default);
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Vect BSSize = S.GetRadius() * Vect(1, 1, 1);
	Vect BSPos = S.GetCenter();
	Matrix World = Matrix(SCALE, BSSize) * Matrix(TRANS, BSPos);
	Instance().privRenderBSphere(World, col);
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& B, const Vect& col)
{
	Instance().privRenderAABB((Matrix &) BoxAttorney::GetAdjWorld(B), col);
}

void Visualizer::ShowAABB(Vect min, Vect max, const Vect& col)
{
	Instance().privRenderAABB(min, max, col);
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& B, const Vect& col)
{
	Instance().privRenderAABB((Matrix &) BoxAttorney::GetAdjWorld(B), col);
}

void Visualizer::ShowVolume(const CollisionVolume& V, Vect& col)
{
	VolumeAttorney::DebugView(V, col);
}

void Visualizer::privRenderBSphere(Matrix &W, const Vect &col)
{
	WFUnitSphere->SetWorld(W);
	WFUnitSphere->SetColor(col);
	WFUnitSphere->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Visualizer::privRenderAABB(Matrix &W, const Vect &col)
{
	WFUnitBox->SetWorld(W);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Visualizer::privRenderAABB(Vect min, Vect max, const Vect &col)
{
	Vect trans = (max + min) * 0.5f;
	Vect scale = max - min;
	Matrix World = (Matrix(SCALE, scale) * Matrix(TRANS, trans)); 
	WFUnitBox->SetWorld(World);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Visualizer::privRenderOBB(Matrix &W, const Vect &col)
{
	WFUnitBox->SetWorld(W);
	WFUnitBox->SetColor(col);
	WFUnitBox->Render(SceneManager::GetCurrentScene()->getCamera());
}

void Visualizer::privVisualizeAll()
{
	for (auto it = sphereList.begin(); it != sphereList.end(); it++)
	{
		(*it)->execute();
	}
	sphereList.clear();
	for (auto it = aabbList.begin(); it != aabbList.end(); it++)
	{
		(*it)->execute();
	}
	aabbList.clear();
	for (auto it = obbList.begin(); it != obbList.end(); it++)
	{
		(*it)->execute();
	}
	obbList.clear();
}

void Visualizer::Delete()
{
	BSphereCommandFactory::Terminate();
	AABBCommandFactory::Terminate();
	OBBCommandFactory::Terminate();
	delete Instance().WFUnitSphere;
	delete Instance().WFUnitBox;
	delete ptrInstance;
	ptrInstance = nullptr;
}