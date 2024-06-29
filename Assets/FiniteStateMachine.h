#pragma once
#include "State.h"
#include "Behaviour.h"


class FiniteStateMachine : public Behaviour
{
private:
    std::vector<State*> m_states;

    std::vector<State::Transition*> trueTransitions;



    State* m_currentState;
    State* m_newState;

public:
    FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) 
    {
        m_currentState = s;
        m_newState = nullptr;
    
    }
    virtual ~FiniteStateMachine();

    virtual void Update(Agent* agent, float deltaTime);

    virtual void Enter(Agent* agent);

    void AddState(State* s)
    {
        if (s == nullptr) { return; }

        m_states.push_back(s);
    }

};

