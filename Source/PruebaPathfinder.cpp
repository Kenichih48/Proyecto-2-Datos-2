#include <iostream>
#include "List_BP.h"
#include "Matrix_BP.h"
#include "Pathfinder.h"

void something(){
    ListBP list1;
    ListBP list2; 
    ListBP list3; 

    for(int i = 0; i < 4; i++){
        NodeBPG* newNode1 = new NodeBPG();
        NodeBPG* newNode2 = new NodeBPG();
        NodeBPG* newNode3 = new NodeBPG();
        newNode1->name = "0";
        newNode2->name = "0";
        newNode3->name = "0";

        list1.append(newNode1);
        list2.append(newNode2);
        list3.append(newNode3);
    }


    MatrixBP* matrix1 = new MatrixBP();
    matrix1->append(list1);
    matrix1->append(list2);
    matrix1->append(list3);

    std::cout << matrix1->at(matrix1->getLength()-1)->at(list1.length -1)->name << std::endl;

    matrix1->at(0)->at(0)->name = "2";
    matrix1->at(0)->at(1)->name = "1";
    matrix1->at(1)->at(2)->name = "1";
    matrix1->at(1)->at(3)->name = "3";

    /*
    matrix1->at(0)->at(0)->name = "3"; 
    matrix1->at(1)->at(0)->name = "1";
    matrix1->at(1)->at(1)->name = "1";
    matrix1->at(1)->at(3)->name = "1";
    matrix1->at(2)->at(0)->name = "2";
    */

    matrix1->print();

    Pathfinder finder; 

    std::cout << "Created finder" << std::endl;

    finder.setField(matrix1);

    std::cout << "Set field success!!" << std::endl;

    finder.setH();

    for(int i = 0; i < finder.getField().getLength(); i++){
        ListBP* newList = finder.getField().at(i);
        for(int j = 0; j < newList->getLength(); j++){
            NodeBPG* newNode = newList->at(j);
            std::cout << newNode->getH() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Set H success!!" << std::endl;

    vector<vector<int>> result = finder.move();

    for(vector<int> elements : result){
        std::cout << "[" << elements.at(0) << "," << elements.at(1) << "]" << std::endl;
    }

    
    ListBP list4;
    ListBP list5;
    ListBP list6;
    ListBP list7;
    ListBP list8;
    ListBP list9;
    ListBP list10;

    for(int i = 0; i < 7; i++){
        NodeBPG* newNode1 = new NodeBPG();
        NodeBPG* newNode2 = new NodeBPG();
        NodeBPG* newNode3 = new NodeBPG();
        NodeBPG* newNode4 = new NodeBPG();
        NodeBPG* newNode5 = new NodeBPG();
        NodeBPG* newNode6 = new NodeBPG();
        NodeBPG* newNode7 = new NodeBPG();

        newNode1->name = "0";
        newNode2->name = "0";
        newNode3->name = "0";
        newNode4->name = "0";
        newNode5->name = "0";
        newNode6->name = "0";
        newNode7->name = "0";

        list4.append(newNode1);
        list5.append(newNode2);
        list6.append(newNode3);
        list7.append(newNode4);
        list8.append(newNode5);
        list9.append(newNode6);
        list10.append(newNode7);
    }

    MatrixBP* matrix2 = new MatrixBP();
    matrix2->append(list4);
    matrix2->append(list5);
    matrix2->append(list6);
    matrix2->append(list7);
    matrix2->append(list8);
    matrix2->append(list9);
    matrix2->append(list10);
    
    matrix2->at(4)->at(1)->name = "2";
    matrix2->at(3)->at(1)->name = "1";
    matrix2->at(1)->at(2)->name = "1";
    matrix2->at(6)->at(2)->name = "1";
    matrix2->at(0)->at(3)->name = "1";
    matrix2->at(3)->at(3)->name = "1";
    matrix2->at(2)->at(4)->name = "1";
    matrix2->at(5)->at(4)->name = "1";
    matrix2->at(1)->at(5)->name = "1";
    matrix2->at(3)->at(5)->name = "1";
    matrix2->at(5)->at(6)->name = "1";
    matrix2->at(3)->at(6)->name = "3";

    matrix2->print();

    Pathfinder finder2; 
    finder2.setField(matrix2);
    finder2.setH();

    for(int i = 0; i < finder2.getField().getLength(); i++){
        ListBP* newList = finder2.getField().at(i);
        for(int j = 0; j < newList->getLength(); j++){
            NodeBPG* newNode = newList->at(j);
            std::cout << newNode->getH() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Set H success!!" << std::endl;

    vector<vector<int>> result2 = finder2.move();

    for(vector<int> elements : result2){
        std::cout << "[" << elements.at(0) << "," << elements.at(1) << "]" << std::endl;
    }     
    
}