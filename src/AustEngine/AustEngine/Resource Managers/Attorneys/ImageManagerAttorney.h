#pragma once

#include "../ImageManager.h"

class ImageManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { ImageManager::Delete(); };
};