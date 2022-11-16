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
    int min = -1, minIndex = -1;
    for (unsigned i = 0; i < aviable.size(); i++)
    {
        cout << "IDO" << endl;
        cout << aviable.at(i)->getId() << endl;
    }
    return 2;
}

int MandatesSelectionPolicy::choose(vector <Party *> aviable,vector<int> * connections)
{
    return 1;
}
