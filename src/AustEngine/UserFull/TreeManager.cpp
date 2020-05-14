#include "TreeManager.h"
#include "Tree.h"
#include "TreeFactory.h"

TreeManager::TreeManager()
{
	TreeCount = 0;
}

void TreeManager::Spawn(Vect v)
{
	TreeArray[TreeCount] = (Tree *)TreeFactory::CreateTree(v);
	TreeArray[TreeCount]->setParent(this);
	TreeArray[TreeCount]->setParentIndex(TreeCount);
	TreeCount++;
}

void TreeManager::Despawn(int index)
{
	TreeCount--;
	TreeArray[index] = nullptr;
}

void TreeManager::Override(int index, StorageNode node)
{
	TreeArray[index]->Recreate(node);
}