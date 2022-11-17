/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#pragma once
//----------USING----------
#include <vector>
using std::vector;
#include <Party.h>
#include <Agent.h>
//---------------------------

#pragma once


class JoinPolicy 
{
public:
    virtual void choose(Agent * agent,Party * party)=0;
};

class MandatesJoinPolicy: public JoinPolicy
{ 
public:
    void choose(Agent * agent,Party * party) override;
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    void choose(Agent * agent,Party * party)override;
};