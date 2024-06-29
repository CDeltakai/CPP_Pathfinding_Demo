#pragma once
#include "Agent.h"
#include "Condition.h"
#include "DistanceCondition.h"


class State
{
public:
    struct Transition
    {
    public:
        Condition* condition;
        State* targetState;
        int priority = 0;

        void SetCondition(Condition* cond)
        {
            condition = cond;
        }
        void SetTargetState(State* state)
        {
            targetState = state;
        }

        void SetPriority(int val)
        {
            priority = val;
        }
    };


private:
    std::vector<Behaviour*> m_behaviours;
    std::vector<Transition> m_transitions;

public:
    State();
    State(Behaviour* behaviour)
    {
        m_behaviours.push_back(behaviour);
    }
    ~State();
    virtual void Enter(Agent* agent);
    virtual void Update(Agent* agent, float deltaTime);
    virtual void Exit(Agent* agent);
    std::vector<Transition> GetTransitions()
    {
        return m_transitions;
    }

    void AddTransition(DistanceCondition* distanceCondtion, State* state, int priority = 0)
    {
        Transition transition{};
        transition.SetCondition(distanceCondtion);
        transition.SetTargetState(state);
        transition.SetPriority(priority);

        m_transitions.push_back(transition);


    }
};

