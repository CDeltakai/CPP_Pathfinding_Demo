#pragma once
#include "Decision.h";

class WanderDecision : public Decision
{
public:

	virtual void MakeDecision(Agent* agent, float deltaTime);

};

