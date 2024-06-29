#include "PathAgent.h"
#include "NodeMap.h"
#include <cmath>
#include <cstdlib>

void PathAgent::Update(float deltaTime)
{
	if (m_path.empty() || m_path.size() == 1 && m_currentIndex == 0) { return; }

	float distanceToNextNode = glm::distance (m_position, m_path[m_currentIndex + 1]->position);

	glm::vec2 directionVector = glm::normalize(m_path[m_currentIndex + 1]->position - m_position);




	float distanceToMove = distanceToNextNode - (m_speed * deltaTime);

	if (distanceToMove > 0)
	{
		m_position += m_speed * deltaTime * directionVector;
	}
	else
	{
		m_currentIndex++;
		//Check if we are at the last node
		if (m_currentIndex == m_path.size() - 1)
		{
			Node* lastNode = m_path.back();
			//m_position = lastNode->position;
			m_path.clear();
			m_currentNode = lastNode;
		}
		else
		{
			float overshootDistance = -distanceToMove;
			// Calculate the direction to the next node in the path
			directionVector = glm::normalize(m_path[m_currentIndex]->position - m_position);
			// Move the agent along this direction by the overshoot distance
			m_position += overshootDistance * directionVector;

		}

	}

	

}

void PathAgent::GoToNode(Node* node)
{
	m_path = NodeMap::AStarSearch(m_currentNode, node);
	if (m_path.size() <= 0)
	{
		return;
	}

	m_currentIndex = 0;
}

void PathAgent::GoToNode(Node* node, NodeMap* nodeMap)
{
	m_path = NodeMap::AStarSearch(nodeMap->GetClosestNode(m_position), node);
	if (m_path.size() <= 0)
	{
		return;
	}

	m_currentIndex = 0;
}

void PathAgent::Draw()
{
	DrawCircle((int)m_position.x, (int)m_position.y, 8, color);
}

