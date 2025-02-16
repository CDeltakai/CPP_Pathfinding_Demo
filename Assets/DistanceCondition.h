#pragma once
#include "Agent.h"
#include "Condition.h"

class DistanceCondition : public Condition
{
private:
    float m_distance;
    bool m_lessThan;

public:
    DistanceCondition(float d, bool lt)
    {
        m_distance = d;
        m_lessThan = lt;
    }
    virtual bool IsTrue(Agent* agent);


};

