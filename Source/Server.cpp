#include <iostream>
#include "List.h"
#include "Matrix.h"

void server(){
    List list1 = List();
    List list2 = List();
    List list3 = List();

    std::cout << "Created lists" << std::endl;


    Matrix newMatrix1 = Matrix();
    newMatrix1.append(list1);
    newMatrix1.append(list2);
    newMatrix1.append(list3);

    Matrix newMatrix2 = Matrix();

    std::cout << "Created Matrix" << std::endl;

    
    List l = newMatrix1.at(1);
    
    
    for(int i = 0; i <= newMatrix1.getLength()-1; i++){
        List list = newMatrix1.at(i);
        std::cout << "Before" << std::endl;
        for(int j = 0; j <= 3; j++){
            list.append("0",0,0,0,true,0);
        }
        std::cout << "After" << std::endl;
        newMatrix2.append(list);
    }

    std::cout << "Appended full lists" << std::endl;

    newMatrix2.print();

    std::cout << "finished print" << std::endl;
}