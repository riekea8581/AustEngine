#include "AABBColCommand.h"
#include "AABBCommandFactory.h"

void AABBColCommand::execute()
{
	VisualizerAttorney::VizDisplay::ShowAABB(*box, color);
	AABBCommandFactory::RecycleCommand(this);
}