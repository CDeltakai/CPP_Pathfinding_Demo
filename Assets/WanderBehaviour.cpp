#include "WanderBehaviour.h"
#include <raylib.h>
#include <raygui.h>
#include "Agent.h"
#include "NodeMap.h"


void WanderBehaviour::Update(Agent* agent, float deltaTime)
{
	if (!agent->PathComplete())
	{
		return;
	}

	NodeMap* nodeMap = agent->GetNodeMap();
	Node* randomNode = nodeMap->GetRandomNode();
	
	agent->GoTo(randomNode->position);
	
	agent->SetColor(Color{ 0, 255, 255, 255 });

}

void WanderBehaviour::Enter(Agent* agent)
{
	std::cout << "Entered wander behaviour" << std::endl;
	agent->SetColor({ 0, 255, 255, 255 }); // cyan
	agent->Reset();

}

