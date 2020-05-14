#pragma once

#include "AzulCore.h"
#include "..\..\Game Object\Commands\Command.h"
#include "..\CollisionVolumeAABB.h"
#include "..\Attorneys\VisualizerAttorney.h"

class AABBColCommand : public Command
{
public:
	AABBColCommand(const CollisionVolumeAABB &b, Vect v)
		:box(&b), color(v) {};
	AABBColCommand(const AABBColCommand&) = delete;
	AABBColCommand& operator=(const AABBColCommand&) = delete;
	~AABBColCommand() {};

	void setColor(Vect v) { color = v; };
	void setBox(const CollisionVolumeAABB &b) { box = &b; };
	virtual void execute();
private:
	const CollisionVolumeAABB * box;
	Vect color;
};