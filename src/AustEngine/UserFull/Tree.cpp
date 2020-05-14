#include "Tree.h"
#include "TreeManager.h"
#include "TreeFactory.h"
#include "Tank.h"
#include "Enemy.h"
#include "..\AustEngine\Resource Managers\ShaderManager.h"
#include "..\AustEngine\Resource Managers\TextureManager.h"
#include "..\AustEngine\Resource Managers\ModelManager.h"
#include "..\AustEngine\Collision\VolumeType.h"
#include <math.h>

Tree::Tree()
{
	Model *pModelEnemyBase = ModelManager::Get("Tree");

	Texture *pEnemyBaseTex = TextureManager::Get("green");

	ShaderObject *pShaderObject_constantColor = ShaderManager::Get("textureLightRender");

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	myModel = new TankModel(pModelEnemyBase, pShaderObject_constantColor, pEnemyBaseTex, LightColor, LightPos);

	SetColliderModel(pModelEnemyBase, VolumeType::AABB);

	colliderColor = Vect(0, 0, 1.0f);

	SetCollidableGroup<Tree>();
}

void Tree::Initialize(Vect & v)
{
	TreeScale.set(SCALE, 10, 10, 10);
	TreePos = v;

	Matrix world = TreeScale * Matrix(ROT_X, -PI / 2) * Matrix(TRANS, TreePos + Vect(0, yOffset, 0));
	myModel->SetWorld(world);
	this->InitializeCollisionData(world);

	health = 5;

	SubmitEntry();
}

void Tree::Draw()
{
	myModel->Render(SceneManager::GetCurrentScene()->getCamera());
	SendColCommand(colliderColor);
}

void Tree::Collision(Tank *)
{
	health = 0;
	parent->Despawn(parentIndex);
	SubmitExit();
}

void Tree::Collision(Enemy *)
{
	health = 0;
	parent->Despawn(parentIndex);
	SubmitExit();
}

void Tree::Collision(Bullet *)
{
	health--;
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void Tree::Collision(EnemyBullet *)
{
	health--;
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void Tree::SceneEntry()
{
	Updatable::SubmitSceneRegistration();
	Drawable::SubmitSceneRegistration();
	SubmitCollisionRegistration();
	StorableManager::StoreElement(this);
	if (health <= 0)
	{
		parent->Despawn(parentIndex);
		SubmitExit();
	}
}

void Tree::SceneExit()
{
	Updatable::SubmitSceneDeregistration();
	Drawable::SubmitSceneDeregistration();
	SubmitCollisionDeregistration();
	TreeFactory::RecycleTree(this);
}

void Tree::Store(StorageNode & node)
{
	strcpy_s(node.tag, "Tree");
	node.v1 = colliderColor;
	node.f1 = health;
}

void Tree::Recreate(const StorageNode & node)
{
	colliderColor = node.v1;
	health = node.f1;
}

Tree::~Tree()
{
	delete myModel;
}