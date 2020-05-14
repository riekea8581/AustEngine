#pragma once

class Collidable;

class CollisionDispatchBase
{
public:
	virtual void ProcessCallbacks(Collidable *, Collidable *) {};
};