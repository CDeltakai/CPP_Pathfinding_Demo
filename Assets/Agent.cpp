#include "Behaviour.h";
#include "Agent.h"
#include "NodeMap.h"


void Agent::Update(float deltaTime)
{
	if (m_current)
	{
		m_current->Update(this, deltaTime);
	}

	m_pathAgent.Update(deltaTime);
}

void Agent::Draw()
{
	m_pathAgent.Draw();
}

void Agent::GoTo(glm::vec2 point)
{
	if (m_pathAgent.end == m_nodeMap->GetClosestNode(point))
	{
		return;
	}

	m_pathAgent.end = m_nodeMap->GetClosestNode(point);

	if (m_pathAgent.end == nullptr) { return; }

	if (glm::distance(m_pathAgent.GetCurrentNode()->position, m_pathAgent.end->position) > 50)
	{
		m_pathAgent.SetNode(m_nodeMap->GetClosestNode(GetPosition()));
	}

	m_pathAgent.GoToNode(m_pathAgent.end, m_nodeMap);
}

void Agent::SetNode(Node* node)
{
	if (!node) { return; }
	m_pathAgent.SetNode(node);
}

bool Agent::PathComplete()
{
	return m_pathAgent.GetPath().empty();
}