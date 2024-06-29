#include "ABDecision.h"



void DecisionNode::MakeDecision(Agent* agent, float deltaTime)
{
	if (condition->IsTrue(agent))
	{
		A->MakeDecision(agent, deltaTime);
		agent->Reset();
	}
	else
	{
		B->MakeDecision(agent, deltaTime);
		agent->Reset();

	}


}


DecisionNode::~DecisionNode()
{
	delete A;
	delete B;
	delete condition;
}
