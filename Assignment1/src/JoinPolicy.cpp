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

void MandatesJoinPolicy::choose(Party * agentParty,Party * party,Coalition * coal)
{
    
    if (agentParty->getMandates() > party->getbestOffer())
    {
        party->setbestOffer(agentParty->getMandates());
        party->setbestAgent(agentParty->getId());
        party->setBestCoal(coal);
    }
    
    cout << "MandatesJoinPolicy" << endl;

}

void LastOfferJoinPolicy::choose(Party * agentParty,Party * party,Coalition * coal) 
{
    party->setbestOffer(agentParty->getMandates());
    party->setbestAgent(agentParty->getId());
    party->setBestCoal(coal);
    cout << "LastOfferJoinPolicy" << endl;
}