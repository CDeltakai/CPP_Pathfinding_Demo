#pragma once
#include "Behaviour.h"
#include "Decision.h"

class DecisionBehaviour : public Behaviour
{
public:
	Decision* m_decision;

	virtual void Update(Agent* agent, float deltaTime)
	{
		m_decision->MakeDecision(agent, deltaTime);
	}


};

