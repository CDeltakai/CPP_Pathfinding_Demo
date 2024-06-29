#include "SelectorBehaviour.h"
#include "Agent.h"
#include "NodeMap.h"

SelectorBehaviour::~SelectorBehaviour()
{
	delete m_b1;
	delete m_b2;
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
    if (m_selected != b)
    {
        m_selected = b;
        agent->Reset();
    }
}

void SelectorBehaviour::Update(Agent* agent, float deltaTime)
{
    if (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < agent->GetNodeMap()->GetCellSize() * 5)
    {
        SetBehaviour(m_b1, agent);
        agent->SetColor({ 255, 0, 0, 255 }); //red
    }
    else
    {
        SetBehaviour(m_b2, agent);
        agent->SetColor({ 0, 255, 255, 255 }); // cyan
    }
    m_selected->Update(agent, deltaTime);
}