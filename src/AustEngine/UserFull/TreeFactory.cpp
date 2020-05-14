#include "TreeFactory.h"
#include "Tree.h"

TreeFactory* TreeFactory::ptrInstance = NULL;

Tree * TreeFactory::privCreateTree(Vect v)
{
	Tree * t;
	if (recycledItems.empty())
	{
		t = new Tree();
		allItems.push(t);
	}
	else
	{
		t = recycledItems.top();
		recycledItems.pop();
	}
	t->Initialize(v);
	return t;
}

void TreeFactory::privRecycleTree(Tree* t)
{
	recycledItems.push(static_cast<Tree*>(t));
}

void TreeFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

TreeFactory::~TreeFactory()
{
	while (!allItems.empty())
	{
		delete allItems.top();
		allItems.pop();
	}
}