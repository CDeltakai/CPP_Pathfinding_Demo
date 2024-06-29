#include "SeekDecision.h"

void SeekDecision::MakeDecision(Agent* agent, float deltaTime)
{
    agent->SetColor(Color{ 255, 0, 0, 255 });
    // check if the agent has moved significantly from its last position
// if so we want to repath towards it
    Agent* target = agent->GetTarget();


    float dist = glm::distance(target->GetPosition(), lastTargetPosition);
    //float dist = glm::distance(target->GetPosition(), agent->GetPosition());


    if (dist > agent->GetNodeMap()->GetCellSize())
    {
        lastTargetPosition = target->GetPosition();
        agent->GoTo(lastTargetPosition);
    }
    //agent->GoTo(target->GetPosition());

}
