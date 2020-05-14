#include "SceneRegistrationBroker.h"
#include "../Game Object/Commands/Command.h"

void SceneRegistrationBroker::addCommand(Command *c)
{
	Iterator it = std::find(cmdList.begin(), cmdList.end(), c);
	if (it == cmdList.end())
		cmdList.push_back(c);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (Iterator it = cmdList.begin(); it != cmdList.end(); it++)
	{
		(*it)->execute();
	}
	cmdList.clear();
}