#include "Pathfinding.h"

#include <glm/glm.hpp>
#include <vector>

using namespace AIForGames;

AIForGames::Node::Node()
{
}

AIForGames::Node::Node(float pos1, float pos2)
{
	position.x = pos1;
	position.y = pos2;
}

void Node::ConnectTo(Node* other, float cost)
{
	connections.push_back(Edge(other, cost));
}