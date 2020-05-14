#pragma once

#include <map>

class ShaderObject;

class ShaderManager
{
	friend class ShaderManagerAttorney;
private:
	static ShaderManager* ptrInstance;

	ShaderManager();

	static ShaderManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager;
		return *ptrInstance;
	}

	std::map < std::string, ShaderObject * > map;
	std::map < std::string, ShaderObject * >::iterator it;

	typedef std::pair< const char *, ShaderObject * > Pair;

	const char * defaultPath = "Shaders/";

	void privLoad(const char *key, const char *path);
	ShaderObject *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, const char *path) { Instance().privLoad(key, path); };
	static ShaderObject *Get(const char *key) { return Instance().privGet(key); };
};