/****************************************
 * Author : Ido Israeli , Raz Marshanski
 * Date   :
 * Name   :
****************************************/
//----------INCLUDE----------
#pragma once
#include <iostream>

class SelectionPolicy 
{
public:
    virtual void choose2()=0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
    virtual void choose2();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
    virtual void choose2();
};



