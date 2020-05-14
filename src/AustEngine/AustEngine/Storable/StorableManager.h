#pragma once

#include "AzulCore.h"
#include <list>

class Storable;

struct StorageNode : public Align16
{
	char tag[16];
	Matrix m1;
	Matrix m2;
	Vect v1;
	Vect v2;
	float f1;
	float f2;
	float f3;
	float f4;
	bool b1;
	bool b2;
	float alarms[3];
};

class StorableManager
{
private:
	static StorableManager* ptrInstance;

	StorableManager() = default;
	StorableManager(const StorableManager&) = delete;
	StorableManager& operator=(const StorableManager&) = delete;
	~StorableManager() {};

	static StorableManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new StorableManager;
		return *ptrInstance;
	}
	
	typedef std::list<Storable*> StorageList;
	typedef StorageList::iterator StorageIterator;
	StorageList storageList;

	void privStoreElement(Storable * s);
	void privUnStoreElement(Storable * s);
	void privRecreateScene();
	void privSerializeAll();
	StorageNode privDeserialize(int offset);
	bool privReadFromFile();
	void privWriteToFile();
	void privClearList() { storageList.clear(); };

	static const int tagLength = 16;
	static const int numObjects = 32; 
	static char tag[tagLength];
	static const int bufLength = sizeof(StorageNode) * numObjects + tagLength + sizeof(int);
	static char buffer[bufLength];
	int storageCount;
	int storageIndex;

	void privSetTag(char * c) { strcpy_s(tag, tagLength, c); };

public:
	static void StoreElement(Storable * s) { Instance().privStoreElement(s); };
	static void UnStoreElement(Storable * s) { Instance().privUnStoreElement(s); };
	static void RecreateScene() { Instance().privRecreateScene(); };
	static void SerializeAll() { Instance().privSerializeAll(); };
	static StorageNode Deserialize(int offset) { return Instance().privDeserialize(offset); };
	static bool ReadFromFile() { return Instance().privReadFromFile(); };
	static void WriteToFile() { Instance().privWriteToFile(); };
	static void ClearList() { return Instance().privClearList(); }
	static int GetCount() { return Instance().storageCount; };
	static int GetIndex() { return Instance().storageIndex; };
	static int GetTagLength() { return Instance().tagLength; };
	static void SetTag(char * c) { Instance().privSetTag(c); };
	static void Terminate();
};