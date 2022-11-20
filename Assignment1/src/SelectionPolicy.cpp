/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <iostream>
#include "SelectionPolicy.h"
#include <utility>

#include <bits/stdc++.h>
using std::cout;
using std::endl;

std::pair<int,int> EdgeWeightSelectionPolicy::choose(vector<Party>parties,vector <int> aviable,vector<int>connections)
{

    int max = 0, maxIndex = -1, partyId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections.at(aviable.at(i)) >max)
        {
            max      = connections.at(aviable.at(i));
            maxIndex = aviable.at(i);
            partyId   = i;
        }
    }
    return(std::make_pair(maxIndex,partyId));
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone()
{
    return new EdgeWeightSelectionPolicy();
}

std::pair<int,int>  MandatesSelectionPolicy::choose(vector<Party>parties,vector <int> aviable,vector<int>connections)
{
    int max = 0, maxIndex = -1, partyId =-1 ;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        
        if ((connections.at(aviable.at(i)) >0) && (parties.at(aviable.at(i)).getMandates() > max) )
        {
            max      = parties.at(aviable.at(i)).getMandates();
            maxIndex = aviable.at(i);
            partyId   = i;
        }
    }
    return(std::make_pair(maxIndex,partyId));
}

MandatesSelectionPolicy* MandatesSelectionPolicy::clone()
{
    return new MandatesSelectionPolicy;
}

