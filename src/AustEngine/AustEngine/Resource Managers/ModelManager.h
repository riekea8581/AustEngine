#pragma once

#include <map>
#include "AzulCore.h"

class Model;

class ModelManager
{
	friend class ModelManagerAttorney;
private:
	static ModelManager* ptrInstance;

	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager() {};

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager;
		return *ptrInstance;
	}

	std::map < std::string, Model * > map;
	std::map < std::string, Model * >::iterator it;

	typedef std::pair< const char *, Model * > Pair;

	const char * defaultPath = "Models/";

	void privLoad(const char *key, const char *path);
	void privLoadPremade(const char *key, Model::PreMadeModels m);
	Model *privGet(const char *key);
	void privDelete();

	static void Delete() { Instance().privDelete(); };

public:
	static void Load(const char *key, const char *path) { Instance().privLoad(key, path); };
	static void LoadPremade(const char *key, Model::PreMadeModels m) { Instance().privLoadPremade(key, m); };
	static Model *Get(const char *key) { return Instance().privGet(key); };
};