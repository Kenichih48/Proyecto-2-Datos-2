#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "Matrix_BP.h"
#include "List_BP.h"

MatrixBP generateCleanMatrix();
MatrixBP generatePlayingfield(int players);
int random_num();

int main(){

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);
    sf::Packet packetS, packetR;

    int numberGoalsInt;
    int numberPlayersInt;
    bool stuff = true;
    srand(time(NULL));

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

    std::cout << std::endl;

    MatrixBP maze = MatrixBP();
    maze = generatePlayingfield(numberPlayersInt);
    string mazeString = maze.print();
    std::cout << mazeString;

    packetS << mazeString;
    socket.send(packetS);

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

MatrixBP generatePlayingfield(int players){
    MatrixBP matrix = MatrixBP();

    for(int i = 0; i <= 6; i++){
        ListBP list = ListBP();
        for(int j = 0; j <= 7; j++){
            list.append("0");
        }
        matrix.append(list);
    }

    matrix.at(3)->at(0)->name = "4";
    matrix.at(3)->at(6)->name = "3";
    matrix.at(3)->at(3)->name = "2";

    int placed = 0;
    int decide;
    while(placed < players/2){
        for(int x = 0; x <= 6;x++){
            for(int y = 0; y <= 2; y++){
               decide = random_num();
               if(decide == 50 && matrix.at(x)->at(y)->name == "0"){
                    matrix.at(x)->at(y)->name = "1";
                    placed++;
                }
            }
        }
    }
    
    while(placed < players){
        for(int x = 0; x <= 6;x++){
            for(int y = 4; y <= 6; y++){
                decide  = random_num();
                if(decide == 50 && matrix.at(x)->at(y)->name == "0"){
                    matrix.at(x)->at(y)->name = "1";
                    placed++;
                }
            }
        }
    }

    return matrix;
}

int random_num(){
    int range = 100;
    int random_int = (rand() % range)+1;
    return random_int;
}

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
