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
    virtual void choose(Party * agentParty,Party * party,Coalition * coal,SelectionPolicy * sp)=0;
};

class MandatesJoinPolicy: public JoinPolicy
{ 
public:
    void choose(Party * agentParty,Party * party,Coalition * coal,SelectionPolicy * sp);
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    void choose(Party * agentParty,Party * party,Coalition * coal,SelectionPolicy * sp);
};