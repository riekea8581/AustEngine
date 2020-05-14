#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\Inputable.h"

typedef GraphicsObject_TextureLight UnpauseHackModel;

class UnpauseHack : public Inputable
{
public:
	UnpauseHack();
	UnpauseHack(const UnpauseHack&) = delete;
	UnpauseHack& operator=(const UnpauseHack&) = delete;
	virtual ~UnpauseHack() {};

	virtual void KeyPressed(AZUL_KEY k);
};