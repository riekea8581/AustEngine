#include "SpriteFontManager.h"
#include "..\Sprite\SpriteFont.h"

SpriteFontManager* SpriteFontManager::ptrInstance = NULL;

SpriteFontManager::SpriteFontManager()
{

}

void SpriteFontManager::privLoad(const char *key, const char *texPath, const char *xmlPath)
{
	char newXmlPath[100];
	strcpy_s(newXmlPath, 100, defaultXmlPath);
	strcat_s(newXmlPath, 100, xmlPath);
	if (map.find(key) == map.end())
		map.insert(Pair(key, new SpriteFont(texPath, newXmlPath)));
	else
		printf("Error: Key already in use");
}

SpriteFont *SpriteFontManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested model");
	return nullptr;
}

void SpriteFontManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, SpriteFont * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}