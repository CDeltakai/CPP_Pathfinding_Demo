#include "FollowBehaviour.h"
#include <raylib.h>
#include <raygui.h>
#include "Agent.h"
#include "NodeMap.h"

#include "Behaviour.h"
#include "Pathfinding.h"
#include <string>
#include "raylib.h"

using namespace AIForGames;


void FollowBehaviour::Update(Agent* agent, float deltaTime)
{
    // check if the agent has moved significantly from its last position
    // if so we want to repath towards it
    Agent* target = agent->GetTarget();


    float dist = glm::distance(target->GetPosition(), lastTargetPosition);
    //float dist = glm::distance(target->GetPosition(), agent->GetPosition());


    if (dist > agent->GetNodeMap()->GetCellSize() * 2)
    {
        lastTargetPosition = target->GetPosition();
        agent->GoTo(lastTargetPosition);
    }
    //agent->GoTo(target->GetPosition());

    agent->SetColor(Color{ 255, 0, 0, 255 });


}

void FollowBehaviour::Enter(Agent* agent)
{
    std::cout << "Entered Follow Behaviour" << std::endl;

    // red when following
    agent->SetColor(Color{ 255,0,0,255 });
    agent->Reset();
}

void FollowBehaviour::Exit(Agent* agent)
{
    std::cout << "Exit Follow Behaviour" << std::endl;
    agent->Reset();
}

