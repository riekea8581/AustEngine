#include "SceneChangeCommand.h"
#include "../SceneManagerAttorney.h"

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::SceneRegistration::ChangeScene(target);
}

void SceneChangeCommand::SetTarget(Scene * s)
{
	target = s;
}