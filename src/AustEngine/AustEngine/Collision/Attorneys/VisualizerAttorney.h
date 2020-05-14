#pragma once

#include "../Visualizer.h"

class VisualizerAttorney
{
public:
	class VizDisplay
	{
	private:
		friend class Scene;
		friend class BSphereColCommand;
		friend class AABBColCommand;
		friend class OBBColCommand; 
		friend class CollisionVolumeBSphere;
		friend class CollisionVolumeAABB; 
		friend class CollisionVolumeOBB;
		friend class TerrainObject;
		static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col) { Visualizer::ShowBSphere(S, col); };
		static void ShowAABB(const CollisionVolumeAABB& B, const Vect& col) { Visualizer::ShowAABB(B, col); };
		static void ShowAABB(const Vect& min, const Vect& max, const Vect& col) { Visualizer::ShowAABB(min, max, col); };
		static void ShowOBB(const CollisionVolumeOBB& B, const Vect& col) { Visualizer::ShowOBB(B, col); };
		static void VisualizeAll() { Visualizer::Instance().privVisualizeAll(); };
	};
	class VizDelete
	{
	private:
		friend class AustEngine;
		static void Delete() { Visualizer::Instance().Delete(); }
	};
};