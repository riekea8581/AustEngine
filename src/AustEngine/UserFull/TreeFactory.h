#pragma once

#include <stack>
#include "AzulCore.h"

class Tree;

class TreeFactory
{
private:
	static TreeFactory* ptrInstance;

	TreeFactory() = default;
	TreeFactory(const TreeFactory&) = delete;
	TreeFactory& operator=(const TreeFactory&) = delete;
	~TreeFactory();

	static TreeFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TreeFactory;
		return *ptrInstance;
	}

	std::stack<Tree*> allItems;
	std::stack<Tree*> recycledItems;

	Tree * privCreateTree(Vect v);
	void privRecycleTree(Tree * t);

public:

	static Tree * CreateTree(Vect v) { return Instance().privCreateTree(v); };
	static void RecycleTree(Tree * t) { Instance().privRecycleTree(t); };
	static void Terminate();
};