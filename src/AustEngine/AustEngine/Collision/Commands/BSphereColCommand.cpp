#include "BSphereColCommand.h"
#include "BSphereCommandFactory.h"

void BSphereColCommand::execute()
{
	VisualizerAttorney::VizDisplay::ShowBSphere(*sphere, color);
	BSphereCommandFactory::RecycleCommand(this);
}