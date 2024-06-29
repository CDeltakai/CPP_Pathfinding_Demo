#pragma once
#include <string>
#include "Behaviour.h"
#include "Agent.h";

class WanderBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent);
	virtual void Exit(Agent* agent) 
	{
		std::cout << "Exit wander behaviour" << std::endl;
		agent->SetColor(Color{ 255, 0, 0, 255 }); // red
		agent->Reset();
	}

	std::string name = "WanderBehaviour";

};

