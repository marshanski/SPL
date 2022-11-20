/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   : SelectionPolicy.h
****************************************/
//----------INCLUDE----------
//----------USING----------
#pragma once
#include <vector>
using std::vector;
#include <Party.h>
#include <iostream>
#include <utility>
//---------------------------


class SelectionPolicy 
{
public:
    virtual std::pair<int,int> choose(vector<Party>parties,vector <int> aviable,vector<int>connections)=0;
    virtual SelectionPolicy* clone()=0;
    virtual ~SelectionPolicy ()=default;

};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
     std::pair<int,int> choose(vector<Party>parties,vector <int> aviable,vector<int>connections);
     MandatesSelectionPolicy* clone() override;
     virtual ~MandatesSelectionPolicy() =default ;

};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
     std::pair<int,int> choose(vector<Party>parties,vector <int> aviable,vector<int>connections);
     EdgeWeightSelectionPolicy* clone()override;
     virtual ~EdgeWeightSelectionPolicy() = default;

};

     

