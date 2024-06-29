#pragma once

#include "Behaviour.h"
#include "Pathfinding.h"
#include <string>
#include "raylib.h"

using namespace AIForGames;



class FollowBehaviour : public Behaviour
{
public:
	virtual void Update(Agent* agent, float deltaTime);

	virtual void Enter(Agent* agent);
	virtual void Exit(Agent* agent);

	std::string name = "FollowBehaviour";

private:
	glm::vec2 lastTargetPosition;

};

