#pragma once
#include "Pathfinding.h"
#include <string>
#include "raylib.h"
#include "NodeMap.h";

using namespace AIForGames;

class PathAgent
{

private:
	glm::vec2 m_position;

	std::vector<Node*> m_path;
	int m_currentIndex;
	Node* m_currentNode;



	float m_speed;

public:
	Node* end;
	void Update(float deltaTime);
	void GoToNode(Node* node);
	void GoToNode(Node* node, NodeMap* nodeMap);
	void Draw();

	Color color = { 255,255,0,255 };

	void SetNode(Node* node)
	{
		if (node == nullptr) { return; }
		m_currentNode = node;

		if (glm::distance(m_position, node->position) > 100)
		{
			m_position = node->position;	

		}

		
	}
	void SetSpeed(float speed)
	{
		m_speed = speed;
	}
	std::vector<Node*> GetPath()
	{
		return m_path;
	}

	Node* GetCurrentNode()
	{
		return m_currentNode;
	}

	glm::vec2 GetPosition()
	{

		return m_position;
	}


};

