#include "GotoPointBehaviour.h"
#include <raylib.h>
#include <raygui.h>
#include "Agent.h"

void GotoPointBehaviour::Update(Agent* agent, float deltaTime)
{
	// read mouseclicks, left for start node, end for right node
	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}


}
