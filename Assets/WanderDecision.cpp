#include "WanderDecision.h"

void WanderDecision::MakeDecision(Agent* agent, float deltaTime)
{
	agent->SetColor(Color{ 0, 255, 0, 255 });

	if (!agent->PathComplete())
	{
		return;
	}

	NodeMap* nodeMap = agent->GetNodeMap();
	Node* randomNode = nodeMap->GetRandomNode();

	agent->GoTo(randomNode->position);



}
