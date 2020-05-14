#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = NULL;

ModelManager::ModelManager()
{

}

void ModelManager::privLoad(const char *key, const char *path)
{
	char newPath[100];
	strcpy_s(newPath, 100, defaultPath);
	strcat_s(newPath, 100, path);
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Model(newPath)));
	else
		printf("Error: Key already in use");
}

void ModelManager::privLoadPremade(const char *key, Model::PreMadeModels m)
{
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Model(m)));
	else
		printf("Error: Key already in use");
}

Model *ModelManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested model");
	return nullptr;
}

void ModelManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, Model * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}