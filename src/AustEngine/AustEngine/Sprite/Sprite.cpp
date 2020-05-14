#include "Sprite.h"
#include "..\Resource Managers\ShaderManager.h"
#include "..\Resource Managers\ImageManager.h"
#include "..\Resource Managers\ModelManager.h"
#include "..\Scene\SceneAttorney.h"

Sprite::Sprite(std::string imgKey)
{
	Model *pModelSprite = ModelManager::Get("UnitSquare2D");
	ShaderObject *pShaderObject_sprite = ShaderManager::Get("spriteRender");
	Image *pImageSprite = ImageManager::Get(imgKey.c_str());

	pGOSprite = new GraphicsObject_Sprite(pModelSprite, pShaderObject_sprite, pImageSprite, pImageSprite->pImageRect);

	centerX = 0.0f;
	centerY = 0.0f;

	posX = pGOSprite->origPosX;
	posY = pGOSprite->origPosY;

	scaleX = 1.0f;
	scaleY = 1.0f;

	angle = 0.0f;

	Matrix Scale(SCALE, scaleX, scaleY, 1.0f);
	Matrix RotZ(ROT_Z, angle);
	Matrix Trans(TRANS, pGOSprite->origPosX, pGOSprite->origPosY, 0.0f);

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);
}

void Sprite::SetCenter(float x, float y)
{
	centerX = x;
	centerY = y;

	Matrix Scale(SCALE, scaleX, scaleY, 1.0f);
	Matrix RotZ(ROT_Z, angle);
	Matrix Trans(TRANS, posX - centerX, posY - centerY, 0.0f);

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);
}

void Sprite::SetPosition(float x, float y)
{
	posX = x;
	posY = y;

	Matrix Scale(SCALE, scaleX, scaleY, 1.0f);
	Matrix RotZ(ROT_Z, angle);
	Matrix Trans(TRANS, posX - centerX, posY - centerY, 0.0f);

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);
}

void Sprite::SetScaleFactor(float x, float y)
{
	scaleX = x;
	scaleY = y;

	Matrix Scale(SCALE, scaleX, scaleY, 1.0f);
	Matrix RotZ(ROT_Z, angle);
	Matrix Trans(TRANS, posX - centerX, posY - centerY, 0.0f);

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);
}

void Sprite::SetScalePixel(float x, float y)
{
	scaleX = x / (pGOSprite->origPosX * scaleX);
	scaleY = y / (pGOSprite->origPosY * scaleY);

	Matrix Scale(SCALE, scaleX, scaleY, 1.0f);
	Matrix RotZ(ROT_Z, angle);
	Matrix Trans(TRANS, posX - centerX, posY - centerY, 0.0f);

	Matrix world = Scale * RotZ * Trans;
	pGOSprite->SetWorld(world);
}

void Sprite::Render()
{
	pGOSprite->Render(SceneManager::GetCurrentScene()->getOrthCamera());
}