#pragma once

#include <map>
#include "AzulCore.h"

class TerrainObject;

class TerrainObjectManager
{
	friend class TerrainObjectManagerAttorney;
private:
	static TerrainObjectManager* ptrInstance;

	TerrainObjectManager() = default;
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator=(const TerrainObjectManager&) = delete;
	~TerrainObjectManager() {};

	static TerrainObjectManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TerrainObjectManager;
		return *ptrInstance;
	}

	std::map < std::string, TerrainObject * > map;
	std::map < std::string, TerrainObject * >::iterator it;

	typedef std::pair< const char *, TerrainObject * > Pair;

	const char * defaultPath = "Textures/";

	void privLoad(const char *key, const char * heightmapFile, Texture * tex, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainObject *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, const char * heightmapFile, Texture * tex, float len, float maxheight, float ytrans, int RepeatU, int RepeatV) { Instance().privLoad(key, heightmapFile, tex, len, maxheight, ytrans, RepeatU, RepeatV); };
	static TerrainObject *Get(const char *key) { return Instance().privGet(key); };
};