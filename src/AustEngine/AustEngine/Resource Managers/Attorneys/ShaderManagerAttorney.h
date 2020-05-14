#pragma once

#include "../ShaderManager.h"

class ShaderManagerAttorney
{
	friend class AustEngine;
private:
	static void Delete() { ShaderManager::Delete(); };
};