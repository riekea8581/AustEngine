#pragma once

#include "SceneCommand.h"

class SceneNullCommand : public SceneCommand
{
	virtual void Execute() {};
};