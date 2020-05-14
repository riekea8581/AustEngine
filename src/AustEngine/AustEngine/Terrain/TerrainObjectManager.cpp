#include "TerrainObjectManager.h"
#include "TerrainObject.h"

TerrainObjectManager* TerrainObjectManager::ptrInstance = NULL;

void TerrainObjectManager::privLoad(const char *key, const char * heightmapFile, Texture * tex, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	char newPath[100];
	strcpy_s(newPath, 100, defaultPath);
	strcat_s(newPath, 100, heightmapFile);
	if (map.find(key) == map.end())
		map.insert(Pair(key, new TerrainObject(newPath, tex, len, maxheight, ytrans, RepeatU, RepeatV)));
	else
		printf("Error: Key already in use");
}

TerrainObject * TerrainObjectManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested model");
	return nullptr;
}

void TerrainObjectManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, TerrainObject * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}