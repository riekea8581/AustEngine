#pragma once

#include "AzulCore.h"
#include <list>

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB; 
class CollisionVolumeOBB;
class BSphereColCommand;
class AABBColCommand;
class OBBColCommand;

class Visualizer : public Align16
{
	friend class VisualizerAttorney;
private:
	static Visualizer * ptrInstance;

	typedef std::list<BSphereColCommand*> BSphereList;
	typedef std::list<AABBColCommand*> AABBList;
	typedef std::list<OBBColCommand*> OBBList;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer() {};

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	}

	static void Delete();

	BSphereList sphereList; 
	AABBList aabbList;
	OBBList obbList;

	GraphicsObject_WireframeConstantColor * WFUnitSphere;
	GraphicsObject_WireframeConstantColor * WFUnitBox;
	static Vect DEFAULT_COLOR;

	static void ShowVolume(const CollisionVolume& V, Vect& col = DEFAULT_COLOR);
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);
	static void ShowAABB(const CollisionVolumeAABB& B, const Vect& col = DEFAULT_COLOR);
	static void ShowAABB(Vect min, Vect max, const Vect& col = DEFAULT_COLOR);
	static void ShowOBB(const CollisionVolumeOBB& B, const Vect& col = DEFAULT_COLOR);
	void privRenderBSphere(Matrix &S, const Vect &col);
	void privRenderAABB(Matrix &S, const Vect &col);
	void privRenderAABB(Vect min, Vect max, const Vect &col);
	void privRenderOBB(Matrix &S, const Vect &col);
	void privAddCommand(BSphereColCommand * cmd) { sphereList.push_back(cmd); };
	void privAddCommand(AABBColCommand * cmd) { aabbList.push_back(cmd); };
	void privAddCommand(OBBColCommand * cmd) { obbList.push_back(cmd); };
	void privVisualizeAll();
public:
	static void AddCommand(BSphereColCommand * cmd) { Visualizer::Instance().privAddCommand(cmd); };
	static void AddCommand(AABBColCommand * cmd) { Visualizer::Instance().privAddCommand(cmd); };
	static void AddCommand(OBBColCommand * cmd) { Visualizer::Instance().privAddCommand(cmd); };
};