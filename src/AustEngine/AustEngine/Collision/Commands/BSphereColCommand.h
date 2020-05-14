#pragma once

#include "AzulCore.h"
#include "..\..\Game Object\Commands\Command.h"
#include "..\CollisionVolumeBSphere.h"
#include "..\Attorneys\VisualizerAttorney.h"

class BSphereColCommand : public Command
{
public:
	BSphereColCommand(const CollisionVolumeBSphere &s, Vect v)
		:sphere(&s), color(v) {};
	BSphereColCommand(const BSphereColCommand&) = delete;
	BSphereColCommand& operator=(const BSphereColCommand&) = delete;
	~BSphereColCommand() {};

	void setColor(Vect v) { color = v; };
	void setSphere(const CollisionVolumeBSphere &s) { sphere = &s; };
	virtual void execute();
private:
	const CollisionVolumeBSphere * sphere;
	Vect color;
};