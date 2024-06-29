#pragma once
#include "Agent.h"



class Decision
{
public:

	virtual void MakeDecision(Agent* agent, float deltaTime) = 0;

	std::string decisionName;
};
