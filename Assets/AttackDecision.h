#pragma once
#include "Decision.h";


class AttackDecision : public Decision
{
public:
	virtual void MakeDecision(Agent* agent, float deltaTime);

	float attackCooldown = 2;
	float currentCooldown = 0;

};

