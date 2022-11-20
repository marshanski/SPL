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


class JoinPolicy 
{
public:
    virtual void choose(Agent * agent,Party * party,int mandates)=0;
};

class MandatesJoinPolicy: public JoinPolicy
{ 
public:
    void choose(Agent * agent,Party * party,int mandates);
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    void choose(Agent * agent,Party * party,int mandates);
};