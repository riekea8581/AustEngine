#pragma once

#include "..\AustEngine\Game Object\GameObject.h"

class Tree;

class TreeManager : public GameObject
{
public:
	TreeManager();
	TreeManager(const TreeManager&) = delete;
	TreeManager& operator=(const TreeManager&) = delete;
	~TreeManager() {};

	void Spawn(Vect v);
	void Override(int index, StorageNode node);
	void Despawn(int index);

private:
	static const int TreeTotal = 10;

	int TreeCount;

	Tree * TreeArray[TreeTotal];
};