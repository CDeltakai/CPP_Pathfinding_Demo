#pragma once
#include "Decision.h"

class SeekDecision : public Decision
{
public:
	virtual void MakeDecision(Agent* agent, float deltaTime);
	glm::vec2 lastTargetPosition;


};

