//#pragma once
#ifndef GENETICPUZZLE_NODEBP_H
#define GENETICPUZZLE_NODEBP_H

#include <iostream>

using namespace std;


template <class T>
class NodeBP
{
public:
    NodeBP *next;
    NodeBP *prev;
    T data;

    void delAll();
    void print();
};

///Deletes all the nodes
template <typename T>
void NodeBP<T>::delAll()
{
    if (next)
        next->delAll();
    delete this;
}

template<typename T>
void NodeBP<T>:: print()
{
    cout << data << endl;
}

#endif //GENETICPUZZLE_NODEBP_H
