#include "AzulCore.h"
#include "..\AustEngine\AustEngine.h"

void AustEngine::AustInitialize()
{
	this->setWindowName("Battle Tank");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
}