#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{
    struct Node;

    struct Edge 
    {
        Node* target;
        float cost;

        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}

    };

    struct Node 
    {
        glm::vec2 position;
        std::vector<Edge> connections;

        float gScore;//indicates the total cost to get here from the current path
        float hScore;//Heuristic score
        float fScore;//Final score: gScore + hScore

        Node* previous;//previous node pointer

    public:
        Node();
        Node(float pos1, float pos2);

        void ConnectTo(Node* other, float cost);

    };




}
