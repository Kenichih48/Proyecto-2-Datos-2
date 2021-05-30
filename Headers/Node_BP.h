#ifndef NODEBP_H_
#define NODEBP_H_

#include <string>

using namespace std;

class NodeBP
{
    private:
        int h = 0;
        int g = 0; 
        int f = 0;
    public:
        string name; //nombre de la variable
        NodeBP* next; //puntero hacia el nodo siguiente en la lista
        NodeBP* prev; //puntero hacia el nodo anterior en la lista
        NodeBP* parent; 
        NodeBP* getParent(){return this->parent;}
        void setParent(NodeBP* parent){this->parent = parent;}
        int getH(){return this->h;}
        int getG(){return this->g;}
        int getF(){return this->f;}
        void setH(int h){this->h = h;}
        void setG(int g){this->g = g;}
        void setF(int f){this->f = f;}
};      

#endif /* NODEBP_H_ */