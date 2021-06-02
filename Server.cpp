#include <iostream>
#include <SFML/Network.hpp>
#include "Matrix_BP.h"
#include "List_BP.h"


//MatrixBP generatePlayingfield(int players){}

MatrixBP generateCleanMatrix(){
    MatrixBP matrix = MatrixBP();

    for(int i = 0; i <= 6; i++){
        ListBP list = ListBP();
        for(int j = 0; j <= 6; j++){
            list.append("0");
        }
        matrix.append(list);
    }

    return matrix;
}

int main(){

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);
    sf::Packet packetS, packetR;

    int numberGoalsInt;
    int numberPlayersInt;
    bool stuff = false;

    while (stuff){
        socket.receive(packetR);
        if(packetR.getData() != NULL){
            packetR >> numberPlayersInt >> numberGoalsInt;
            std::cout <<  numberPlayersInt << numberGoalsInt << std::endl;
            break;
        }
    }
    

    MatrixBP matrix = MatrixBP();
    matrix = generateCleanMatrix();
    matrix.print();

     
    /*
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

    std::cout << "finished print" << std::endl;*/
}