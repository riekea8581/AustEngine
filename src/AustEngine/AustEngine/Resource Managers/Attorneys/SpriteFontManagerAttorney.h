#pragma once

#include "../SpriteFontManager.h"

class SpriteFontManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { SpriteFontManager::Delete(); };
};