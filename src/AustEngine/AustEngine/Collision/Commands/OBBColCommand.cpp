#include "OBBColCommand.h"
#include "OBBCommandFactory.h"

void OBBColCommand::execute()
{
	VisualizerAttorney::VizDisplay::ShowOBB(*box, color);
	OBBCommandFactory::RecycleCommand(this);
}