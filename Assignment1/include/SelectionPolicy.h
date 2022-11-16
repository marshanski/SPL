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
//---------------------------

class SelectionPolicy 
{
public:
    virtual int choose(vector<Party *> aviable,vector<int> * connections)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
    int choose(vector<Party *> aviable,vector<int> * connections) override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
    int choose(vector<Party *> aviable, vector<int> * connections) override;
};



