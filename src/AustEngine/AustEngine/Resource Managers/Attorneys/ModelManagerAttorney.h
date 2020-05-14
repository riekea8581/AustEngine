#pragma once

#include "../ModelManager.h"

class ModelManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { ModelManager::Delete(); };
};