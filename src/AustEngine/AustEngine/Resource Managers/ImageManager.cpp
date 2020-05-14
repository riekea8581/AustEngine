#include "ImageManager.h"
#include "AzulCore.h"

ImageManager* ImageManager::ptrInstance = NULL;

ImageManager::ImageManager()
{

}

void ImageManager::privLoad(const char *key, Texture * tex)
{
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Image(tex, new Rect(0.0f, 0.0f, (float) tex->getWidth(), (float) tex->getHeight()))));
	else
		printf("Error: Key already in use");
}

void ImageManager::privLoad(const char *key, Texture * tex, Rect * r)
{
	if (map.find(key) == map.end())
		map.insert(Pair(key, new Image(tex, r)));
	else
		printf("Error: Key already in use");
}

Image *ImageManager::privGet(const char *key)
{
	it = map.find(key);
	if (it != map.end())
		return it->second;
	else
		printf("Error: Couldn't find the requested model");
	return nullptr;
}

void ImageManager::privDelete()
{
	it = map.begin();
	while (it != map.end())
	{
		std::map < std::string, Image * >::iterator tmp = it;
		std::advance(it, 1);
		delete tmp->second;
	}
	delete ptrInstance;
	ptrInstance = nullptr;
}