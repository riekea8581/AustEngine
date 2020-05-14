#pragma once

#include <map>
#include "AzulCore.h"

class Texture;

class TextureManager
{
	friend class TextureManagerAttorney;
private:
	static TextureManager* ptrInstance;

	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager() {};

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager;
		return *ptrInstance;
	}

	std::map < std::string, Texture * > map;
	std::map < std::string, Texture * >::iterator it;

	typedef std::pair< const char *, Texture * > Pair;

	const char * defaultPath = "Textures/";

	void privLoad(const char *key, const char *path);
	void privLoadPix(const char *key, Vect v);
	Texture *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, const char *path) { Instance().privLoad(key, path); };
	static void LoadPix(const char *key, Vect v) { Instance().privLoadPix(key, v); };
	static Texture *Get(const char *key) { return Instance().privGet(key); };
};