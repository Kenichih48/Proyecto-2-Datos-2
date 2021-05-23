#ifndef NODE_H_
#define NODE_H_

#include <string>

using namespace std;

class Node
{
    public:
        string name; //nombre de la variable
        int memory_value; //cantidad de memoria requerida para almacenar la variable
        int offset; //el offset en donde se encuentra la memoria en la variable
        int count; //la cantidad de runs que la variable tiene sin ser utilizado
        bool mark; //la marca de variable indicando si se encuentra presente en cada run del cliente
        int references; //la cantidad de veces que la variable ha estado presente
        Node* next; //puntero hacia el nodo siguiente en la lista
        Node* prev; //puntero hacia el nodo anterior en la lista
};

#endif /* NODE_H_ */