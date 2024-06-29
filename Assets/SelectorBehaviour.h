#pragma once
#include "Behaviour.h"

class SelectorBehaviour : public Behaviour
{
private:
    Behaviour* m_b1;
    Behaviour* m_b2;
    Behaviour* m_selected;

public:
    SelectorBehaviour(Behaviour* b1, Behaviour* b2) : m_b1(b1), m_b2(b2) {}
    ~SelectorBehaviour();

    void SetBehaviour(Behaviour* b, Agent* agent);



    virtual void Update(Agent* agent, float deltaTime);

};

