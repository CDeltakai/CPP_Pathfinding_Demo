#include "FiniteStateMachine.h"

FiniteStateMachine::~FiniteStateMachine()
{
    // the FSM owns every State assigned to it
    for (State* s : m_states)
        delete s;
}

void FiniteStateMachine::Update(Agent* agent, float deltaTime)
{
    State* newState = nullptr;
    State::Transition highestPriorityTransition;
    bool foundValidTransition = false;

    // check the current state's transitions
    for (State::Transition t : m_currentState->GetTransitions())
    {
        if (t.condition->IsTrue(agent))
        {


            //newState = t.targetState;
            //std::cout << "FSM switched state"  << std::endl;

            // Initialize highestPriorityTransition on first valid transition
            if (!foundValidTransition || t.priority > highestPriorityTransition.priority)
            {
                highestPriorityTransition = t;
                foundValidTransition = true;
            }

        }
    }

    // If a valid transition was found, set the new state
    if (foundValidTransition)
    {
        newState = highestPriorityTransition.targetState;
        std::cout << "FSM switched state" << std::endl;
    }


    // if we've changed state, clean up the old one and initialise the new one
    if (newState != nullptr && newState != m_currentState)
    {
        m_currentState->Exit(agent);
        m_currentState = newState;
        m_currentState->Enter(agent);
    }


    // update the current state
    m_currentState->Update(agent, deltaTime);
}

void FiniteStateMachine::Enter(Agent* agent)
{
    m_currentState->Enter(agent);
}