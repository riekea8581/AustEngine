#include "KeyEventManager.h"
#include "../Game Object/Inputable.h"
#include "../Game Object/Attorneys/InputableAttorney.h"

KeyEventManager::KeyEventManager(AZUL_KEY k)
{
	myKey = k;
	lastFramePressed = false;
	firstFrame = true;
}

void KeyEventManager::ProcessEvents()
{
	bool currFramePressed = Keyboard::GetKeyState(myKey);
	if (currFramePressed == true && lastFramePressed == false && firstFrame == false)
	{
		for (EventIterator it = pressList.begin(); it != pressList.end(); it++)
		{
			InputableAttorney::InputGameLoop::KeyPressed(*it, myKey);
		}
	}
	if (currFramePressed == false && lastFramePressed == true)
	{
		for (EventIterator it = releaseList.begin(); it != releaseList.end(); it++)
		{
			InputableAttorney::InputGameLoop::KeyReleased(*it, myKey);
		}
	}
	lastFramePressed = currFramePressed;
	firstFrame = false;
}

void KeyEventManager::Register(Inputable * i, EVENT_TYPE e)
{
	switch (e)
	{
	case(EVENT_TYPE::KEY_PRESS):
		InputableAttorney::InputGameLoop::setRef(i, pressList.insert(pressList.end(), i));
		break;
	case(EVENT_TYPE::KEY_RELEASE):
		InputableAttorney::InputGameLoop::setRef(i, releaseList.insert(releaseList.end(), i));
		break;
	}
}

void KeyEventManager::Deregister(Inputable * i, EVENT_TYPE e)
{
	switch (e)
	{
	case(EVENT_TYPE::KEY_PRESS):
		pressList.erase(InputableAttorney::InputGameLoop::getRef(i));
		break;
	case(EVENT_TYPE::KEY_RELEASE):
		releaseList.erase(InputableAttorney::InputGameLoop::getRef(i));
		break;
	}
}