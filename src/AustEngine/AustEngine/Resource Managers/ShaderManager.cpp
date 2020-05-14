#include "ShaderManager.h"
#include "AzulCore.h"

ShaderManager* ShaderManager::ptrInstance = NULL;

ShaderManager::ShaderManager()
{

}

void ShaderManager::privLoad(const char *key, const char *path)
{
	char newPath[100];
	strcpy_s(newPath, 100, defaultPath);
	strcat_s(newPath, 100, path);
	if (map.find(key) == map.end())
		map.insert(Pair(key, new ShaderObject(newPath)));
	else
		printf("Error: Key already in use");
}

ShaderObject *ShaderManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested shader");
	return nullptr;
}

void ShaderManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, ShaderObject * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}