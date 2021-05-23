#ifndef MATRIX_H_
#define MATRIX_H_

#include "List.h"

class MatrixNode{
    private: 
        List* element; 
        MatrixNode* next; 
        MatrixNode* last;
    public: 
        MatrixNode(){
            this->element = nullptr;
            this->next = nullptr;
            this->last = nullptr;
        }
        List getElement(){return *(this->element);}
        MatrixNode* getNext(){return this->next;}
        MatrixNode* getLast(){return this->last;}
        void setElement(List* list){this->element = list;}
        void setNext(MatrixNode* next){this->next = next;}
        void setLast(MatrixNode* last){this->last = last;}
 };

 class Matrix{
    private:
        MatrixNode* tail = NULL; 
        MatrixNode* head = NULL;
        int length = 0;
    public: 
        Matrix(){}
        int getLength(){return this->length;}
        bool isEmpty(){return this->length == 0;}
        void append(List newlist){
            if(this->isEmpty()){
                List* newlistPtr = new List;
                *newlistPtr = newlist; 
                head = new MatrixNode;
                head->setElement(newlistPtr);
                tail = head; 
                this->length++;
            } else{ 
                List* newlistPtr = new List;
                *newlistPtr = newlist;
                MatrixNode* newNodePtr = new MatrixNode;
                newNodePtr->setElement(newlistPtr);
                tail->setNext(newNodePtr);
                newNodePtr->setLast(tail);
                tail = newNodePtr;
                this->length++;
            }
        }
        void print(){
            if(!this->isEmpty()){
                MatrixNode* currentNode;
                currentNode = head; 
                while (currentNode != NULL){
                    List currentList = currentNode->getElement();
                    currentList.printList();
                    currentNode = currentNode->getNext();
                }
            }
        }
        List at(int index){
            int currentIndex = 0;
            if(index > this->length || index < 0){
                throw;
            } else{ 
                MatrixNode* currentNode;
                currentNode = head; 
                std::cout << "Before while" << std::endl;
                while(currentIndex < index){
                    currentNode = currentNode->getNext();
                    currentIndex++;
                }
                std::cout << "After While"  << currentNode << std::endl;
                return currentNode->getElement();
            }
        }
 };

#endif /* MATRIX_H_ */