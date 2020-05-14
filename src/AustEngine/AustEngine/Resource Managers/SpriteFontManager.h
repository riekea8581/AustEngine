#pragma once

#include <map>
#include "AzulCore.h"

class SpriteFont;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
private:
	static SpriteFontManager* ptrInstance;

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() {};

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteFontManager;
		return *ptrInstance;
	}

	std::map < std::string, SpriteFont * > map;
	std::map < std::string, SpriteFont * >::iterator it;

	typedef std::pair< const char *, SpriteFont * > Pair;

	const char * defaultXmlPath = "XML/";

	void privLoad(const char *key, const char *texPath, const char *xmlPath);
	SpriteFont *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, const char *texPath, const char *xmlPath) { Instance().privLoad(key, texPath, xmlPath); };
	static SpriteFont *Get(const char *key) { return Instance().privGet(key); };
};