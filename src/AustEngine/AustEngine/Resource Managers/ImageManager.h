#pragma once

#include <map>

class Image;
class Texture;
struct Rect;

class ImageManager
{
	friend class ImageManagerAttorney;
private:
	static ImageManager* ptrInstance;

	ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	~ImageManager() {};

	static ImageManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ImageManager;
		return *ptrInstance;
	}

	std::map < std::string, Image * > map;
	std::map < std::string, Image * >::iterator it;

	typedef std::pair< const char *, Image * > Pair;

	void privLoad(const char *key, Texture *tex);
	void privLoad(const char *key, Texture *tex, Rect * r); 
	Image *privGet(const char *key);
	void privDelete();
	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, Texture * tex) { Instance().privLoad(key, tex); };
	static void Load(const char *key, Texture * tex, Rect * r) { Instance().privLoad(key, tex, r); }; 
	static Image *Get(const char *key) { return Instance().privGet(key); };
};