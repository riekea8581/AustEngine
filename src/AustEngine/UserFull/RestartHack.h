#pragma once

#include "AzulCore.h"
#include "..\AustEngine\Game Object\Inputable.h"

typedef GraphicsObject_TextureLight RestartHackModel;

class RestartHack : public Inputable
{
public:
	RestartHack();
	RestartHack(const RestartHack&) = delete;
	RestartHack& operator=(const RestartHack&) = delete;
	virtual ~RestartHack() {};

	virtual void KeyPressed(AZUL_KEY k);
};