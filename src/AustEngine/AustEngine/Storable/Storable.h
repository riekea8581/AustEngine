#pragma once

#include "..\Scene\SceneManager.h"
#include "StorableManager.h"

class Storable
{
public:
	Storable() {};
	Storable(const Storable&) = delete;
	Storable& operator=(const Storable&) = delete;
	virtual ~Storable() {};
	/// \brief User-defined function that stores relevant data in a given StorageNode.
	/// 
	/// \ingroup UIEVENTS
	/// 
	/// The way the storable system works is by having specific objects store their
	/// most important data in a struct and retrieving it later, and that is done in
	/// this function. The passed-in struct has two matrices, two vectors, four floats,
	/// and two bools to store data in. It also has a C-string "nametag" that should be
	/// used to identify the object within, and a size-3 array for alarm data. The user-
	/// defined version of this method should store relevant data in these variables and
	/// set its nametag based on the object type.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an object storing its data in the float & bool variables
	/// of the struct, then setting its nametag as "ObjectType1".
	///
	/// \code
	/// 
	/// void Object::Store(StorageNode & node)
	/// {
	/// 	strcpy_s(node.tag, "ObjectType1");
	/// 	node.f1 = myHealth;
	/// 	node.b1 = AmIDead;
	/// }
	/// \endcode
	virtual void Store(StorageNode & ) {};
	/// \brief User-defined function that extracts relevant data from a given StorageNode.
	/// 
	/// \ingroup UIEVENTS
	/// 
	/// The way the storable system works is by having specific objects store their
	/// most important data in a struct and retrieving it later, and that is done in
	/// this function. The passed-in struct has two matrices, two vectors, four floats,
	/// and two bools to store data in. It also has a C-string "nametag" that should be
	/// used to identify the object within, and a size-3 array for alarm data. The user-
	/// defined version of this method should extract relevant data from these variables
	/// based on what was stored in them in the Storable::Store() function.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an object setting its data based on the values in the
	///  float & bool variables of the struct.
	///
	/// \code
	/// 
	/// void Object::Recreate(StorageNode & node)
	/// {
	/// 	strcpy_s(node.tag, "ObjectType1");
	/// 	myHealth = node.f1;
	/// 	AmIDead = node.b1;
	/// }
	/// \endcode
	virtual void Recreate(const StorageNode & ) {};
};