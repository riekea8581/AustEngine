#include "WorldAxis.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"

WorldAxis::WorldAxis()
{
	Model *pModelAxis = ModelManager::Get("Axis");
	ShaderObject *pShaderObject_colorNoTexture = ShaderManager::Get("colorNoTextureRender");
	axis = new Axis(pModelAxis, pShaderObject_colorNoTexture);
	Matrix world = Matrix(IDENTITY);
	axis->SetWorld(world);

	Drawable::SubmitSceneRegistration();
}

void WorldAxis::Draw()
{
	axis->Render(SceneManager::GetCurrentScene()->getCamera());
}

WorldAxis::~WorldAxis()
{
	delete axis;
}