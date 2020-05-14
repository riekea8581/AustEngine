#pragma once

#include "AzulCore.h"
#include "..\..\Game Object\Commands\Command.h"
#include "..\CollisionVolumeOBB.h"
#include "..\Attorneys\VisualizerAttorney.h"

class OBBColCommand : public Command
{
public:
	OBBColCommand(const CollisionVolumeOBB &b, Vect v)
		:box(&b), color(v) {};
	OBBColCommand(const OBBColCommand&) = delete;
	OBBColCommand& operator=(const OBBColCommand&) = delete;
	~OBBColCommand() {};

	void setColor(Vect v) { color = v; };
	void setBox(const CollisionVolumeOBB &b) { box = &b; };
	virtual void execute();
private:
	const CollisionVolumeOBB * box;
	Vect color;
};