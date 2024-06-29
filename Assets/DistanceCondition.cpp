#include "DistanceCondition.h"

#include "Behaviour.h"
#include "Pathfinding.h"
#include <string>
#include "raylib.h"
#include <cmath>
#include <cstdlib>

using namespace AIForGames;


bool DistanceCondition::IsTrue(Agent* agent)
{
	float dist = glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition());


	//std::cout << "distance: " + std::to_string(dist) << std::endl;
	//std::cout << "Condition: " + std::to_string(glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) << std::endl;


	return (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < m_distance) == m_lessThan;
}
