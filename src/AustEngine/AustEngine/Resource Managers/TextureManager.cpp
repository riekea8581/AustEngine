#include "TextureManager.h"
#include "AzulCore.h"

TextureManager* TextureManager::ptrInstance = NULL;

TextureManager::TextureManager()
{

}

void TextureManager::privLoad(const char *key, const char *path)
{
	char newPath[100];
	strcpy_s(newPath, 100, defaultPath);
	strcat_s(newPath, 100, path);
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Texture(newPath)));
	else
		printf("Error: Key already in use");
}

void TextureManager::privLoadPix(const char *key, Vect v)
{
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Texture((unsigned char) v.X(), (unsigned char) v.Y(), (unsigned char) v.Z())));
	else
		printf("Error: Key already in use");
}

Texture *TextureManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested model");
	return nullptr;
}

void TextureManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, Texture * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}