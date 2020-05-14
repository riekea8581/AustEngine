#include "StorableManager.h"
#include "Storable.h"
#include <fstream>

StorableManager* StorableManager::ptrInstance = NULL;
char StorableManager::buffer[] = { 0 };
char StorableManager::tag[] = { 0 };

void StorableManager::privStoreElement(Storable * s)
{
	storageList.push_back(s);
}

void StorableManager::privUnStoreElement(Storable * s)
{
	storageList.remove(s);
}

void StorableManager::privSerializeAll()
{
	memcpy(buffer, tag, tagLength);
	int offset = tagLength;
	StorageNode node;
	for (StorageIterator it = storageList.begin(); it != storageList.end(); it++)
	{
		(*it)->Store(node);
		memcpy(buffer + offset, &node, sizeof(StorageNode));
		offset += sizeof(StorageNode);
		if (offset > bufLength)
			assert(false && "Too Many Objects Have Been Stored!");
	}
	storageCount = storageList.size();
	storageList.clear();
}

StorageNode StorableManager::privDeserialize(int offset)
{
	StorageNode node;
	memcpy(&node, buffer + offset, sizeof(StorageNode));
	return node;
}

bool StorableManager::privReadFromFile()
{
	FILE * inFile1;
	FILE * inFile2;
	errno_t err;
	if ((err = fopen_s(&inFile1, "StoreFile.txt", "r")) != 0)
		return false;
	if ((err = fopen_s(&inFile2, "CountFile.txt", "r")) != 0)
		return false;
	fread(buffer, sizeof(char), bufLength, inFile1);
	fread(&storageCount, sizeof(char), sizeof(int), inFile2);
	fclose(inFile1);
	fclose(inFile2);
	return true;
}

void StorableManager::privWriteToFile()
{
	remove("StoreFile.txt");
	remove("CountFile.txt");
	FILE * inFile1;
	FILE * inFile2;
	errno_t err;
	if ((err = fopen_s(&inFile1, "StoreFile.txt", "w")) != 0)
		assert(false && "Cannot Open Data File");
	if ((err = fopen_s(&inFile2, "CountFile.txt", "w")) != 0)
		assert(false && "Cannot Storage Count File");
	fwrite(buffer, sizeof(char), bufLength, inFile1);
	fwrite(&storageCount, sizeof(char), sizeof(int), inFile2);
	fclose(inFile1); 
	fclose(inFile2);
}

void StorableManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}