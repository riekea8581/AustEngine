#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\Inputable.h"

typedef GraphicsObject_TextureLight StartHackModel;

class StartHack : public Inputable
{
public:
	StartHack();
	StartHack(const StartHack&) = delete;
	StartHack& operator=(const StartHack&) = delete;
	virtual ~StartHack() {};

	virtual void KeyPressed(AZUL_KEY k);
};