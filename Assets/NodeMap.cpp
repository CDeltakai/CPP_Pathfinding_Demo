#include "NodeMap.h"
#include <string>
#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>

using namespace AIForGames;


bool CompareNodesByGScore(Node* a, Node* b)
{
    return a->gScore < b->gScore;
}

Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
{
	int x = (int)(worldPos.x / m_cellSize);
    if (x < 0)
    {

        x = 0;
        std::cout << "Clicked space was less than 0, x set to 0";
    }else
        if (x >= m_width)
        {
            x = m_width - 1;
            std::cout << "Clicked space was greater than map width, x set to closest value";
        }

	// do the same for y
	int y = (int)(worldPos.y / m_cellSize);
    if (y < 0)
    {
		y = 0;
		std::cout << "Clicked space was less than 0, y set to 0";
	}
	else
		if (y >= m_height)
		{
			y = m_height - 1;
			std::cout << "Clicked space was greater than map height, y set to closest value";
		}

	return GetNode(x, y);
}

std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
    if (!startNode || !endNode)
    {
        throw std::runtime_error("Invalid input nodes");
    }

    if (startNode == endNode)
    {
        return std::vector<Node*>();
    }

    //Initalise starting node
    startNode->gScore = 0;
    startNode->previous = nullptr;

    std::vector<Node*> openList; //stores nodes currently being processed
    std::vector<Node*> closedList; //stores nodes already processed

    openList.push_back(startNode);

    Node* currentNode = startNode;

    while (!openList.empty())
    {
        std::sort(openList.begin(), openList.end(), CompareNodesByGScore);//sort from smallest to biggest

        currentNode = openList[0];

        if (currentNode == endNode)
        {
            break;
        }

        openList.erase(openList.begin());
        closedList.push_back(currentNode);

        for (const Edge& edge : currentNode->connections)
        {
            //If target is not in closed list
            if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end())
            {
                float gScore = currentNode->gScore + edge.cost;

                //If target is not in open list
                if (std::find(openList.begin(), openList.end(), edge.target) == openList.end())
                {
                    edge.target->gScore = gScore;
                    edge.target->previous = currentNode;
                    openList.push_back(edge.target);

                }else
                    if (gScore < edge.target->gScore)//Node already in open list with valid score
                    {
                        edge.target->gScore = gScore;
                        edge.target->previous = currentNode;


                    }
            }
        }

    }

	if (openList.empty()) 
    {
		return std::vector<Node*>(); // Return an empty path
	}

    if (currentNode != endNode)
    {

		// No path exists from startNode to endNode.
		return std::vector<Node*>();  // Return an empty path.
    }

    std::vector<Node*> path;

    currentNode = endNode;

    while (currentNode)
    {
        path.insert(path.begin(), currentNode);
        currentNode = currentNode->previous;
    }

    return path;
}

std::vector<Node*> NodeMap::AStarSearch(Node* startNode, Node* endNode)
{
	if (!startNode || !endNode)
	{
		throw std::runtime_error("Invalid input nodes");
	}

	if (startNode == endNode)
	{
		return std::vector<Node*>();
	}

	// Initialise the starting node
	startNode->gScore = 0;
	startNode->hScore = glm::distance(startNode->position, endNode->position); // Heuristic
	startNode->fScore = startNode->gScore + startNode->hScore;
	startNode->previous = nullptr;

	std::vector<Node*> openList; // stores nodes currently being processed
	std::vector<Node*> closedList; // stores nodes already processed

	openList.push_back(startNode);

	Node* currentNode = nullptr;

	while (!openList.empty())
	{
		// Sort openList by Node.fScore
		std::sort(openList.begin(), openList.end(), [](Node* a, Node* b) 
        {
	        return a->fScore < b->fScore;
	    });

		currentNode = openList[0];

		if (currentNode == endNode)
		{
			break;
		}

		openList.erase(openList.begin());
		closedList.push_back(currentNode);

		for (const Edge& edge : currentNode->connections)
		{
			if (std::find(closedList.begin(), closedList.end(), edge.target) == closedList.end())
			{
				float gScore = currentNode->gScore + edge.cost;
				float hScore = glm::distance(edge.target->position, endNode->position); // Heuristic
				float fScore = gScore + hScore;

				if (std::find(openList.begin(), openList.end(), edge.target) == openList.end())
				{
					edge.target->gScore = gScore;
					edge.target->hScore = hScore;
					edge.target->fScore = fScore;

					edge.target->previous = currentNode;
					openList.push_back(edge.target);
				}
				else 
                    if (fScore < edge.target->fScore)
					{
						edge.target->gScore = gScore;
						edge.target->hScore = hScore;
						edge.target->fScore = fScore;

						edge.target->previous = currentNode;
					}
			}
		}
	}

	if (openList.empty())
	{
		return std::vector<Node*>(); // Return an empty path
	}

	std::vector<Node*> path;
	currentNode = endNode;

	while (currentNode)
	{
		path.insert(path.begin(), currentNode);
		currentNode = currentNode->previous;
	}

	return path;
}



void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
{
    this->internalAsciiMap = asciiMap;


    m_cellSize = cellSize;
    const char emptySquare = '0';

    // assume all strings are the same length, so we'll size the map according
    // to the number of strings and the length of the first one
    m_height = asciiMap.size();
    m_width = asciiMap[0].size();

    m_nodes = new Node * [m_width * m_height];

    // loop over the strings, creating Node entries as we go
    for (int y = 0; y < m_height; y++)
    {
        std::string& line = asciiMap[y];

        if (line.size() != m_width)
            std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;

        for (int x = 0; x < m_width; x++)
        {
            // get the x-th character, or return an empty node if the string         
            // isn't long enough
            char tile = x < line.size() ? line[x] : emptySquare;

            // create a node for anything but a '.' character
            m_nodes[x + m_width * y] = tile == emptySquare ? nullptr
                : new Node(((float)x + 0.5f) * m_cellSize, ((float)y + 0.5f) * m_cellSize);
        }
    }

   //loop over the nodes, creating connections between each node and its      
// neighbour to the West and South on the grid. this will link up all nodes
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node)
            {
                // see if there's a node to our west, checking for array overruns      
                // first if we're on the west-most edge
                Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                if (nodeWest)
                {
                    node->ConnectTo(nodeWest, 1); 
                    nodeWest->ConnectTo(node, 1);
                }

                // see if there's a node south of us, checking for array index
                // overruns again
                Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                if (nodeSouth)
                {
                    node->ConnectTo(nodeSouth, 1);
                    nodeSouth->ConnectTo(node, 1);
                }
            }
        }
    }




}


void NodeMap::Draw()
{
    // red color for the blocks
    Color cellColor;
    cellColor.a = 255;
    cellColor.r = 255;
    cellColor.g = 0;
    cellColor.b = 0;

    Color lineColor;//grey
    lineColor.a = 255;
    lineColor.r = 100;
    lineColor.g = 100;
    lineColor.b = 100;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Node* node = GetNode(x, y);
            if (node == nullptr)
            {
                // draw a solid block in empty squares without a navigation node
                DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                    (int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
            }
            else
            {
                // draw the connections between the node and its neighbours
                for (int i = 0; i < node->connections.size(); i++)
                {
                    Node* other = node->connections[i].target;
                    DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize,
                        (int)other->position.x, (int)other->position.y,
                        lineColor);
                }
            }
        }
    }
}



void NodeMap::DrawPath(std::vector<Node*> nodePath, Color lineColor)
{
    Color actualLineColor = lineColor;

    Color startLineColor;//green line for start node
	startLineColor.a = 255;
	startLineColor.r = 0;
	startLineColor.g = 128;
	startLineColor.b = 0;

    Color endLineColor;//red line for end node
	endLineColor.a = 255;
	endLineColor.r = 255;
	endLineColor.g = 0;
	endLineColor.b = 0;

    if (nodePath.size() <= 0)
    {
        return;
    }

    for (int i = 0; i < nodePath.size() - 1; i++)
    {
        

        Node* currentNode = nodePath[i];
        Node* nextNode = nodePath[i + 1];

        if (i == 0)
        {
            actualLineColor = startLineColor;
        }
        if (i == nodePath.size() - 2)
        {
            actualLineColor = endLineColor;
        }

        DrawLine((int)(currentNode->position.x + 0.5f), (int)(currentNode->position.y + 0.5f),
            (int)nextNode->position.x, (int)nextNode->position.y,
            actualLineColor);

        actualLineColor = lineColor;
    }

}


Node* NodeMap::GetRandomNode()
{
    Node* node = nullptr;
    while (node == nullptr)
    {
        int x = rand() % m_width;
        int y = rand() % m_height;
        node = GetNode(x, y);
    }
    return node;
}

