#ifndef LISTBP_H_
#define LISTBP_H_

#include "Node_BP.h"
#include <iostream>
#include <sstream>

using namespace std;

class ListBP{
    public:
        int length = 0;

        int getLength(){return this->length;}

        NodeBPG* head = NULL; //El primer nodo de la lista
        /**
         * @brief Prepara el primer nodo de la lista
         * @param new_head Recibe un puntero de un nodo
        **/
        void set_head(NodeBPG* new_head){ //asigna un nodo recibido como el primer nodo de la lista
            head = new_head;
        }

        /**
         * @brief Agrega un nodo al final de la lista
         * @param new_name nombre que será guardado
         * @param new_memory valor de memoria que será guardado
         * @param new_offset valor de offset que será guardado 
         * @param new_count valor de count que será guardado
         * @param new_mark valor de marcador que será guardado
         * @param new_references valor de reference que será guardado
        **/
        void append(string new_name) //dado los datos, añade un nodo con los datos recibidos al final de la lista
        {
            NodeBPG* new_node = new NodeBPG();  //se crea un nodo nuevo     
            NodeBPG* last = head;

            // se asignan los valores al nuevo nodo
            new_node->name = new_name;
            new_node->next = NULL;

            if (head == NULL) //caso añadir nodo a una lista vacía
            {
                new_node->prev = NULL;
                head = new_node;
                length++;
                return;
            }
            while (last->next != NULL) //while para llegar al final de la lista
                {last = last->next;}
            last->next = new_node; //se asigna el último nodo como el nodo nuevo
            new_node->prev = last;  
            this->length++;      
            return;
        }

        void append(NodeBPG* newNode){     
            NodeBPG* last = head;
            newNode->next = NULL;

            if (head == NULL) //caso añadir nodo a una lista vacía
            {
                newNode->prev = NULL;
                head = newNode;
                length++;
                return;
            }
            while (last->next != NULL){
                last = last->next;
            }
            last->next = newNode; //se asigna el último nodo como el nodo nuevo
            newNode->prev = last;  
            this->length++;      
            return;
        }
        /**
         * @brief borra un nodo indicado de lista
         * @param del nodo que será borrado de lista
         * @return el nodo que fue borrado
        **/
        NodeBPG* deleteNode(NodeBPG* del) //función para borrar un nodo dado de la lista, este nodo es luego retornado para luego ser agregado a collector
        {
            if (head == NULL || del == NULL) //caso particular
                {//return;
                }
        
            if (head == del) //caso cuando el nodo que será borrado es el primer nodo
                {head = del->next;}
        
            if (del->next != NULL) //el nodo siguiente se cambia siempre y cuando no es el último nodo de la lista
                {del->next->prev = del->prev;}
        
            if (del->prev != NULL) //el nodo anterior se cambia siempre y cuando no es el primero nodo de la lista
                {del->prev->next = del->next;}
        
            //Se retorna el nodo que será borrado
            this->length--;
            return del;
        }

        /**
         * @brief imprime todos los elementos de la lista
        **/
        string printList() //Función que imprime todos los nombres de los elementos en la lista
        {
            NodeBPG* node = head;
            stringstream ss;
            cout<<"\nEstado de la lista: \n";
            while (node != NULL)
            {
                cout<<" "<<node->name<<" ";
                ss << node->name;
                node = node->next;
            }
            return ss.str();
        }

        /**
         * @brief función que revisa si algún nodo de la lista tiene el nombre especificado
         * @param input_name el nombre que se desea ver si está en la lista o no
         * @return un bool indicando si existe un nodo con el nombre especificado o no
        **/
        int check_list(string input_name){ //Función que revisa si el elemento dado existe en la lista
            NodeBPG* node = head;
            int position = 0;
            while (node != NULL)
            {
                if (node->name == input_name){
                    return position;
                }
                else{
                    node = node->next;
                    position++;
                }
            }
            return -1;
        }

        NodeBPG* at(int position){
            NodeBPG* result = new NodeBPG();
            NodeBPG* current = this->head;
            result->name ="Empty";
            int i = 0;
            if(position < this->length && position >= 0){
                while(i < position){
                    current = current->next;
                    i++;
                }
                return current;
            }
            return result; 
        }
};

#endif /* LIST_H_ */