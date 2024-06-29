#pragma once

#include "Behaviour.h"
#include "PathAgent.h"
#include <iostream>
class NodeMap;
class Behaviour;

class Agent
{
public:

	Agent() {}
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 })
	{
		if (_nodeMap == nullptr || _behaviour == nullptr) { return; }
		m_nodeMap = _nodeMap;
		m_current = _behaviour;
		m_current->Enter(this);
		m_pathAgent.SetSpeed(100);
		m_pathAgent.color = m_color;
	}

	~Agent() { delete m_current; }

	void Update(float deltaTime);
	void Draw();
	void GoTo(glm::vec2 point);
	void SetNode(Node* node);
	void SetPathAgent(PathAgent pathAgent)
	{
		m_pathAgent = pathAgent;
	}


	bool PathComplete();

	NodeMap* GetNodeMap()
	{
		return m_nodeMap;
	}

	void SetTarget(Agent* agent)
	{
		if (agent == nullptr) 
		{
			std::cout << "Given agent target was nullptr" << std::endl;
			
			return; 
		}
		
		target = agent;
	}

	Agent* GetTarget()
	{
		return target;
	}

	glm::vec2 GetPosition()
	{
		return m_pathAgent.GetPosition();
	}

	void SetSpeed(float speed)
	{
		m_pathAgent.SetSpeed(speed);
	}

	void SetColor(Color color)
	{
		m_pathAgent.color = color;
	}

	void Reset()
	{
		m_pathAgent.GetPath().clear();

	}

private:
	PathAgent m_pathAgent;
	NodeMap* m_nodeMap;
	Behaviour* m_current;
	Color m_color;

	Agent* target;

};

