#ifndef MATRIXBP_H_
#define MATRIXBP_H_

#include "List_BP.h"
#include <sstream>

/**
 * @file Matrix_BP.h
 * @version 1.0
 * @title Matrix_BP
 * @brief Objeto matriz utilizado para algoritmo pathfinding a* y backtracking
 */

class MatrixNodeBPG{
    private: 
        ListBP* element; 
        MatrixNodeBPG* next; 
        MatrixNodeBPG* last;
    public: 
        MatrixNodeBPG(){
            this->element = nullptr;
            this->next = nullptr;
            this->last = nullptr;
        }
        ListBP* getElement(){return this->element;}
        MatrixNodeBPG* getNext(){return this->next;}
        MatrixNodeBPG* getLast(){return this->last;}
        void setElement(ListBP* list){this->element = list;}
        void setNext(MatrixNodeBPG* next){this->next = next;}
        void setLast(MatrixNodeBPG* last){this->last = last;}
 };

 class MatrixBP{
    private:
        MatrixNodeBPG* tail = NULL; 
        MatrixNodeBPG* head = NULL;
        int length = 0;
    public: 
        MatrixBP(){}
        int getLength(){return this->length;}
        bool isEmpty(){return this->length == 0;}

        /**
         * @brief agrega una lista al fondo de la matriz
         * @param ListBP lista a agregar
         **/
        void append(ListBP newlist){
            if(this->isEmpty()){
                ListBP* newlistPtr = new ListBP;
                *newlistPtr = newlist; 
                head = new MatrixNodeBPG;
                head->setElement(newlistPtr);
                tail = head; 
                this->length++;
            } else{ 
                ListBP* newlistPtr = new ListBP;
                *newlistPtr = newlist;
                MatrixNodeBPG* newNodePtr = new MatrixNodeBPG;
                newNodePtr->setElement(newlistPtr);
                tail->setNext(newNodePtr);
                newNodePtr->setLast(tail);
                tail = newNodePtr;
                this->length++;
            }
        }

        /**
         * @brief imprime cada lista de la matriz
         **/ 
        string print(){
            stringstream ss;
            if(!this->isEmpty()){
                MatrixNodeBPG* currentNode;
                currentNode = head; 
                while (currentNode != NULL){
                    ListBP* currentList = currentNode->getElement();
                    string listString = currentList->printList();
                    ss << listString;
                    currentNode = currentNode->getNext();
                }
            }
            return ss.str();
        }

        /**
         * @brief accede a la posicion indicada de la matriz 
         * @param int index posicion a ser accesada
         * @return ListBP* puntero a la posicion indicada 
         * (retorn una excepción si no puede ser accesada)
         **/ 
        ListBP* at(int index){
            int currentIndex = 0;
            if(index > this->length || index < 0){
                throw;
            } else{ 
                MatrixNodeBPG* currentNode;
                currentNode = head; 
                //std::cout << "Before while" << std::endl;
                while(currentIndex < index){
                    currentNode = currentNode->getNext();
                    currentIndex++;
                }
                //std::cout << "After While"  << currentNode << std::endl;
                return currentNode->getElement();
            }
        }
 };

#endif /* MATRIXBP_H_ */