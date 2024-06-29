#pragma once
#include "Pathfinding.h"
#include <string>
#include "raylib.h"

using namespace AIForGames;

class NodeMap
{
public:
    Node* GetClosestNode(glm::vec2 worldPos);
    static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
	static std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);


    int m_width, m_height;
    float m_cellSize = 50;

    
    Node** m_nodes;

public:
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    std::vector<std::string> internalAsciiMap;


    Node* GetNode(int x, int y) 
    {
		if (y < 0 || y >= internalAsciiMap.size() || x < 0 || x >= internalAsciiMap[y].length()) 
        {
			return nullptr; // Either x or y or both are out of bounds
		}


		if (internalAsciiMap[y][x] == '0')
        {
			return nullptr; // Return null if the node is a wall or doesn't exist
		}
        return m_nodes[x + m_width * y]; 
    
    }

    void Draw();

    void DrawPath(std::vector<Node*> nodePath, Color lineColor);

    Node* GetRandomNode();

    float GetCellSize()
    {
        return m_cellSize;
    }

};

