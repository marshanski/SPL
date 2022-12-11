/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#include<JoinPolicy.h>
#include <iostream>
//----------USING----------
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
void MandatesJoinPolicy::update(Agent * agent,Party * party,int mandates)
{
    if (mandates > party->getbestOffer())
    {
        party->setbestOffer(mandates);
        party->setbestAgent(agent->getPartyId());
        party->setBestCoal(agent->getColId());
    }
}

MandatesJoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy();
}

void LastOfferJoinPolicy::choose(Agent * agent,Party * party,int mandates)
{
    
    party->setbestOffer(mandates);
    party->setbestAgent(agent->getPartyId());
    party->setBestCoal(agent->getColId());
    

}
LastOfferJoinPolicy* LastOfferJoinPolicy::clone()
{
    return new LastOfferJoinPolicy();
}

void LastOfferJoinPolicy::update(Agent * agent,Party * party,int mandates)
{
    return;
}
