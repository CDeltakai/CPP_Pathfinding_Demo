/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "Pathfinding.h"
#include "NodeMap.h"
#include <string>
#include "PathAgent.h"
#include "Agent.h"
#include "GotoPointBehaviour.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "DistanceCondition.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include "ABDecision.h";
#include "AttackDecision.h"
#include "DecisionBehaviour.h"
#include "WanderDecision.h"
#include "SeekDecision.h"

using namespace AIForGames;




int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 600;
    int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------


    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111010");
    asciiMap.push_back("000000000000");

    NodeMap* nodeMap = new NodeMap();
    nodeMap->Initialise(asciiMap, 50);

    Node* start = nodeMap->GetNode(1, 1);
    Node* end = nodeMap->GetNode(10, 2);
	std::vector<Node*> nodeMapPath = NodeMap::AStarSearch(start, end);

    Color lineColor = { 255, 255, 255, 255 };


    PathAgent pathAgent;
    pathAgent.SetNode(start);
    pathAgent.SetSpeed(100);
    
	Agent agent(nodeMap, new GotoPointBehaviour());
	agent.SetNode(start);
    

    Agent wanderingAgent(nodeMap, new WanderBehaviour());
    wanderingAgent.SetNode(nodeMap->GetRandomNode());

    Agent followingAgent(nodeMap, new FollowBehaviour());
    followingAgent.SetTarget(&agent);
    followingAgent.SetNode(nodeMap->GetRandomNode());
    followingAgent.SetSpeed(32);
    followingAgent.SetColor({ 255,0,0, 255 });

    // set up a FSM, we're going to have two states with their own conditions
    DistanceCondition* closerThan5 = new DistanceCondition(3.0f * nodeMap->GetCellSize(), true);
    DistanceCondition* furtherThan7 = new DistanceCondition(5.0f * nodeMap->GetCellSize(), false);

    // register these states with the FSM, so its responsible for deleting them now
    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());
    wanderState->AddTransition(closerThan5, followState);
    followState->AddTransition(furtherThan7, wanderState);

    // make a finite state machine that starts off wandering
    FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(followState);




    Agent agent3(nodeMap, fsm);
    agent3.SetNode(nodeMap->GetRandomNode());
    agent3.SetTarget(&agent);
    agent3.SetSpeed(40);


    //Decision Tree Agent
    DistanceCondition* closerThan3 = new DistanceCondition(3.0f * nodeMap->GetCellSize(), true);
    DistanceCondition* closerThan1 = new DistanceCondition(nodeMap->GetCellSize(), true);


    DecisionNode* decisionNode1 = new DecisionNode();
    decisionNode1->decisionName = "abDecision1";
    decisionNode1->B = new WanderDecision();
    decisionNode1->B->decisionName = "WanderDecision";
    decisionNode1->condition = closerThan3;

    DecisionNode* decisionNode2 = new DecisionNode();
    decisionNode2->decisionName = "abDecision2";
    decisionNode2->A = new AttackDecision();
    decisionNode2->A->decisionName = "AttackDecision";
    decisionNode2->B = new SeekDecision();
    decisionNode2->B->decisionName = "SeekDecision";
    decisionNode2->condition = closerThan1;

    decisionNode1->A = decisionNode2;

    DecisionBehaviour* decisionBehaviour = new DecisionBehaviour();
    decisionBehaviour->m_decision = decisionNode1;



    Agent decisionTreeAgent(nodeMap, decisionBehaviour);
    decisionTreeAgent.SetNode(nodeMap->GetRandomNode());
    decisionTreeAgent.SetTarget(&agent);
    decisionTreeAgent.SetSpeed(50);





    float time = (float)GetTime();
    float deltaTime;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		float fTime = (float)GetTime();
		deltaTime = fTime - time;
		time = fTime;


		if (IsMouseButtonPressed(0))//Set start node and make agent move
		{
			Vector2 mousePos = GetMousePosition();
			start = nodeMap->GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
			if (start != nullptr && end != nullptr)
			{
				nodeMapPath = NodeMap::AStarSearch(start, end);
                pathAgent.SetNode(start);
                pathAgent.GoToNode(end);

            }

		}
		if (IsMouseButtonPressed(1))//Set end node
		{
			Vector2 mousePos = GetMousePosition();
			end = nodeMap->GetClosestNode(glm::vec2(mousePos.x, mousePos.y));

            if (end != nullptr && start != nullptr)
            {
				nodeMapPath = NodeMap::AStarSearch(start, end);

            }

		}

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        nodeMap->Draw();
        nodeMap->DrawPath(nodeMapPath, lineColor);


        agent.Update(deltaTime);
        agent.Draw();


        decisionTreeAgent.Update(deltaTime);
        decisionTreeAgent.Draw();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


