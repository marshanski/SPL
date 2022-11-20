/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#pragma once
//----------USING----------
#include<JoinPolicy.h>
#include <iostream>
using std::cout;
using std::endl;
//---------------------------
void MandatesJoinPolicy::choose(Agent * agent,Party * party,int mandates)
{
    
    if (mandates > party->getbestOffer())
    {
        party->setbestOffer(mandates);
        party->setbestAgent(agent->getPartyId());
        party->setBestCoal(agent->getColId());
    }
    

}

void LastOfferJoinPolicy::choose(Agent * agent,Party * party,int mandates)
{
    party->setbestOffer(mandates);
    party->setbestAgent(agent->getPartyId());
    party->setBestCoal(agent->getColId());
}