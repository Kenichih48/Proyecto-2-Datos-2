#ifndef LIST_H_
#define LIST_H_

#include "Node.h"
#include <iostream>

using namespace std;

class List{
    public:
        Node* head; //El primer nodo de la lista
        /**
         * @brief Prepara el primer nodo de la lista
         * @param new_head Recibe un puntero de un nodo
        **/
        void set_head(Node* new_head){ //asigna un nodo recibido como el primer nodo de la lista
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
        void append(string new_name, int new_memory, int new_offset, int new_count, bool new_mark, int new_references) //dado los datos, añade un nodo con los datos recibidos al final de la lista
        {
            Node* new_node = new Node();  //se crea un nodo nuevo     
            Node* last = head;

            // se asignan los valores al nuevo nodo
            new_node->name = new_name;
            new_node->memory_value = new_memory;
            new_node->offset = new_offset;
            new_node->count = new_count;
            new_node->mark = new_mark;
            new_node->references = new_references;
            new_node->next = NULL;

            if (head == NULL) //caso añadir nodo a una lista vacía
            {
                new_node->prev = NULL;
                head = new_node;
                return;
            }
            while (last->next != NULL) //while para llegar al final de la lista
                {last = last->next;}
            last->next = new_node; //se asigna el último nodo como el nodo nuevo
            new_node->prev = last;        
            return;
        }
        /**
         * @brief borra un nodo indicado de lista
         * @param del nodo que será borrado de lista
         * @return el nodo que fue borrado
        **/
        Node* deleteNode(Node* del) //función para borrar un nodo dado de la lista, este nodo es luego retornado para luego ser agregado a collector
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
            return del;
        }

        /**
         * @brief imprime todos los elementos de la lista
        **/
        void printList() //Función que imprime todos los nombres de los elementos en la lista
        {
            Node* node = head;
            cout<<"\nEstado de la lista: \n";
            while (node != NULL)
            {
                cout<<" "<<node->name<<" ";
                node = node->next;
            }
        }

        /**
         * @brief función que revisa si algún nodo de la lista tiene el nombre especificado
         * @param input_name el nombre que se desea ver si está en la lista o no
         * @return un bool indicando si existe un nodo con el nombre especificado o no
        **/
        bool check_list(string input_name){ //Función que revisa si el elemento dado existe en la lista
            Node* node = head;
            while (node != NULL)
            {
                if (node->name == input_name){
                    node->count = 0; //Se resetea el conteo de no estar presente en runs
                    node->references += 1; //se suma uno a la cantidad de veces llamado
                    node->mark = true; //Se marca el elemento como presente
                    return true;
                }
                else{
                    node = node->next;
                }
            }
            return false;
        }

        /**
         * @brief busca el offset almacenado en un nodo que tenga el nombre especificado
         * @param input_name el nombre especificado para buscar su offset respectivo
         * @return el offset del nodo con el nombre correcto
        **/
        int find_offset(string input_name){ //Función que retorna el offset de un elemento indicado
            Node* node = head;
            while (node != NULL)
            {
                if (node->name == input_name){
                    return node->offset;
                }
                else{
                    node = node->next;
                }
            }
            return 0;
        }

        /**
         * @brief busca la cantidad de veces que se ha llamado una variable
         * @param input_name el nombre especificado para buscar su conteo respectivo
         * @return la cantidad de veces que se ha llamado la variable
        **/
        int find_count(string input_name){ //Función que retorna el references de un elemento indicado
            Node* node = head;
            while (node != NULL)
            {
                if (node->name == input_name){
                    return node->references;
                }
                else{
                    node = node->next;
                }
            }
            return 0;
        }

        /**
         * @brief le suma uno al count de todos los elementos en la lista que no estaban presentes en un run
        **/
        void add_counts(){ //función que suma un count a todos los elementos que no estaban presentes en el run
            Node* node = head;
            while (node != NULL)
            {
                if (node->mark == false){
                    node->count += 1;
                }
                node = node->next;
            }
        }

        /**
         * @brief resetea las marcas de todos los nodos a false
        **/
        void reset_marks(){ //función que resetea todas las marcas, preparándo la lista para el siguiente run
            Node* node = head;
            while (node != NULL)
            {
                node->mark = false;
                node = node->next;
            }
        }

};

#endif /* LIST_H_ */