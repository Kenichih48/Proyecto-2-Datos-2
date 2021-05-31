#ifndef GENETICPUZZLE_LISTGP_H
#define GENETICPUZZLE_LISTGP_H

#include <iostream>
#include "MatrixGP.h"
#include "NodeBP.h"

using namespace std;

template <class T>
class ListGP
{
public:
    ListGP();
    ~ListGP();


    void addData(T);
    void addGeneration(T);
    void delAll();
    void delData(T);
    void print();

    int getSize();
    T getDataPos(int);
    NodeBP<T>* getHead();

private:
    int numNodes;
    NodeBP<T>* head = NULL;
};

///Default constructor
template <typename T>
ListGP<T>::ListGP()
{
    numNodes = 0;
    head = NULL;
}

///Add a node data at the end of the list
template <typename T>
void ListGP<T>::addData(T data_)
{
    NodeBP<T> *newNode = new NodeBP<T>;
    newNode->data = data_;
    newNode->next = NULL;
    NodeBP<T>* temp = head;
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    numNodes++;
}

template <typename T>
void ListGP<T>::addGeneration(T data_)
{
    NodeBP<T>* newNode = new NodeBP<T>;
    newNode->data = data_;
    //newMatrix->printMatrix();
    newNode->next = NULL;
    NodeBP<T>* temp = head;
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
        //cout << "head: " << head << " - temp: " << temp << endl;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        //cout << "head: " << head << " - temp: " << temp << endl;
    }
    temp = NULL;
    numNodes++;
}

///Deletes all the nodes
template <typename T>
void ListGP<T>::delAll()
{
    head->delAll();
    head = 0;
}

///Delete a node of the list by data
template <typename T>
void ListGP<T>::delData(T data_)
{
    NodeBP<T> *temp = head;
    NodeBP<T> *temp1 = head->next;

    if(head->data == data_)
    {
        head = temp->next;
        head->prev = NULL;
    } else {
        while(temp1)
        {
            if(temp1->data == data_)
            {
                temp->next = temp1->next;
                temp->prev = temp1->prev->prev;
                temp1 = NULL;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
    }
    numNodes--;
}

///Gets the size of the list
template <typename T>
int ListGP<T>::getSize()
{
    return numNodes;
}

///Get the data of the node by position
template <typename T>
T ListGP<T>::getDataPos(int index)
{
    NodeBP<T> *temp = head;
    int count = 0;

    while(temp != NULL)
    {
        if(count == index)
        {
            return temp->data;
        }
        count++;
        temp = temp->next;
    }
}

///Gets the head of the list
template <typename T>
NodeBP<T>* ListGP<T>::getHead() {
    return ListGP::head;
}

///Prints the list node by node
template <typename T>
void ListGP<T>::print()
{
    NodeBP<T> *temp = head;
    if(!head){
        cout << "La lista esta vacia" << endl;
    } else {
        while(temp != NULL){
            temp->print();
            temp = temp->next;
        }
    }
}

///Deconstructor
template <typename T>
ListGP<T>::~ListGP() = default;

#endif //GENETICPUZZLE_LISTGP_H
