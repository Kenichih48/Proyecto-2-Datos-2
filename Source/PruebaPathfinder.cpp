#include <iostream>
#include "List_BP.h"
#include "Matrix_BP.h"
#include "Pathfinder.h"

MatrixBP generateMatrixFrom(string matrixString);

/**
 * @brief Ejemplo de funcionalidad Pathfinder
 **/
int tryExample(){
    MatrixBP matrix1 = generateMatrixFrom("00100000000000100010100041001030020000000000100000100000");
    matrix1.print();
    Pathfinder finder; 
    finder.setField(&matrix1);
    finder.setH();
    for(int i = 0; i < finder.getField().getLength(); i++){
        ListBP* newList = finder.getField().at(i);
        for(int j = 0; j < newList->getLength(); j++){
            NodeBPG* newNode = newList->at(j);
            std::cout << newNode->getH() << " ";
        }
        std::cout << std::endl;
    }
    vector<vector<int>> result = finder.move();
    for(vector<int> elements: result){
        std::cout << elements.at(0) << "," << elements.at(1) << std::endl;
    }
}

MatrixBP generateMatrixFrom(string matrixString){
    MatrixBP matrix = MatrixBP();

    for(int i = 0; i <= 6; i++){
        ListBP list = ListBP();
        for(int j = 0; j <= 7; j++){
            string s;
            char c; 
            c = matrixString[j+(8*i)];
            s += c;
            if(((j+(8*i))+1) % 8 > 0){
                list.append(s);
            }
        }
        matrix.append(list);
    }

    return matrix;
}
