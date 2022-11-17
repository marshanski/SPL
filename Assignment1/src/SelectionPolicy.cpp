/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : Coalitaion.h
****************************************/
//----------INCLUDE----------
#pragma once
#include <iostream>
#include "SelectionPolicy.h"
using std::cout;
using std::endl;


int EdgeWeightSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    //cout << aviable.size() << endl;
    cout << "IDO" << endl;
    int max = 0, maxIndex = -1;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        if (connections->at(aviable.at(i)->getId()) >max)
        {
            max      = connections->at(aviable.at(i)->getId());
            maxIndex = aviable.at(i)->getId();
        }
    }
    
    cout << max << endl;
    return 2;
}

int MandatesSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    return 1;
}
