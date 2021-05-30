#ifndef MATRIXBP_H_
#define MATRIXBP_H_

#include "List_BP.h"

class MatrixNodeBP{
    private: 
        ListBP* element; 
        MatrixNodeBP* next; 
        MatrixNodeBP* last;
    public: 
        MatrixNodeBP(){
            this->element = nullptr;
            this->next = nullptr;
            this->last = nullptr;
        }
        ListBP* getElement(){return this->element;}
        MatrixNodeBP* getNext(){return this->next;}
        MatrixNodeBP* getLast(){return this->last;}
        void setElement(ListBP* list){this->element = list;}
        void setNext(MatrixNodeBP* next){this->next = next;}
        void setLast(MatrixNodeBP* last){this->last = last;}
 };

 class MatrixBP{
    private:
        MatrixNodeBP* tail = NULL; 
        MatrixNodeBP* head = NULL;
        int length = 0;
    public: 
        MatrixBP(){}
        int getLength(){return this->length;}
        bool isEmpty(){return this->length == 0;}
        void append(ListBP newlist){
            if(this->isEmpty()){
                ListBP* newlistPtr = new ListBP;
                *newlistPtr = newlist; 
                head = new MatrixNodeBP;
                head->setElement(newlistPtr);
                tail = head; 
                this->length++;
            } else{ 
                ListBP* newlistPtr = new ListBP;
                *newlistPtr = newlist;
                MatrixNodeBP* newNodePtr = new MatrixNodeBP;
                newNodePtr->setElement(newlistPtr);
                tail->setNext(newNodePtr);
                newNodePtr->setLast(tail);
                tail = newNodePtr;
                this->length++;
            }
        }
        void print(){
            if(!this->isEmpty()){
                MatrixNodeBP* currentNode;
                currentNode = head; 
                while (currentNode != NULL){
                    ListBP currentList = *(currentNode->getElement());
                    currentList.printList();
                    currentNode = currentNode->getNext();
                }
            }
        }
        ListBP* at(int index){
            int currentIndex = 0;
            if(index > this->length || index < 0){
                throw;
            } else{ 
                MatrixNodeBP* currentNode;
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

#endif /* MATRIXBP_H_ */