#pragma once

#include <list>

class Command;

class SceneRegistrationBroker
{
public:
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() {};
	
	void addCommand(Command *c);
	void ExecuteCommands();
private:
	typedef std::list<Command*> CommandList;
	typedef CommandList::iterator Iterator;
	CommandList cmdList;
};