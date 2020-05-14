#include "WorldPlane.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"

WorldPlane::WorldPlane()
{
	Model *pModelPlane = ModelManager::Get("Plane");
	Texture *pTextPlane = TextureManager::Get("ground");
	ShaderObject *pShaderObject_texture = ShaderManager::Get("textureFlatRender");
	plane = new Plane(pModelPlane, pShaderObject_texture, pTextPlane);
	Matrix world = Matrix(SCALE, 1600, 1600, 1600);
	plane->SetWorld(world);

	Drawable::SubmitSceneRegistration();
}

void WorldPlane::Draw()
{
	plane->Render(SceneManager::GetCurrentScene()->getCamera());
}

WorldPlane::~WorldPlane()
{
	delete plane;
}