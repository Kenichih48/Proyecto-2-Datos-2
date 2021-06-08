#ifndef NODEBP_H_
#define NODEBP_H_

#include <string>

/**
 * @file Node_BP.h
 * @version 1.0
 * @title Node_BP
 * @brief Nodo para Lista_BP
 */

using namespace std;

class NodeBPG
{
    private:
        int h = 0;
        int g = 0; 
        int f = 0;
    public:
        string name; //nombre de la variable
        NodeBPG* next; //puntero hacia el nodo siguiente en la lista
        NodeBPG* prev; //puntero hacia el nodo anterior en la lista
        NodeBPG* parent = NULL; 
        NodeBPG* getParent(){return this->parent;}
        void setParent(NodeBPG* parent){this->parent = parent;}
        int getH(){return this->h;}
        int getG(){return this->g;}
        int getF(){return this->f;}
        void setH(int h){this->h = h;}
        void setG(int g){this->g = g;}
        void setF(int f){this->f = f;}
};      

#endif /* NODEBP_H_ */