#include "WallPlane.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Camera Manager\CameraManager.h"
#include "..\AustEngine\Scene\SceneManager.h"

WallPlane::WallPlane(Matrix mat, Texture * tex)
{
	Model *pModelPlane = ModelManager::Get("Plane");
	Texture *pTextPlane = tex;
	ShaderObject *pShaderObject_texture = ShaderManager::Get("textureFlatRender");
	plane = new Plane(pModelPlane, pShaderObject_texture, pTextPlane);
	plane->SetWorld(mat);

	Drawable::SubmitSceneRegistration();
}

void WallPlane::Draw()
{
	plane->Render(SceneManager::GetCurrentScene()->getCamera());
}

WallPlane::~WallPlane()
{
	delete plane;
}