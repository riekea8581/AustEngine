#pragma once

#include "../TextureManager.h"

class TextureManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { TextureManager::Delete(); };
};