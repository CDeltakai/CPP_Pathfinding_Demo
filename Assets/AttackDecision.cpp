#include "AttackDecision.h"

void AttackDecision::MakeDecision(Agent* agent, float deltaTime)
{
	currentCooldown += deltaTime;
	if (currentCooldown >= attackCooldown)
	{
		currentCooldown = 0;
		std::cout << "Attacked agent"  << std::endl;
	}


}
