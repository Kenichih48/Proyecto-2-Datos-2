#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "Matrix_BP.h"
#include "List_BP.h"
#include "Pathfinder.h"

MatrixBP generateCleanMatrix();
MatrixBP generatePlayingfield(int players);
int random_num();
MatrixBP generateSolution(MatrixBP maze, MatrixBP sol, int ball_x, int ball_y);
bool generateSolution_aux(MatrixBP maze, int x, int y, MatrixBP sol);
bool check_safety(MatrixBP maze, int x, int y);

int main(){
    
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);
    sf::Packet packetS, packetR;

    int numberGoalsInt;
    int numberPlayersInt;
    int turn;
    int old_ball_x = 3;
    int old_ball_y = 3;
    int new_ball_x;
    int new_ball_y;
    bool running = true;
    bool first_run = false;
    srand(time(NULL));

    MatrixBP maze = MatrixBP();

    while (running){
        if (first_run != true){
            while(true){
                socket.receive(packetR);
                if(packetR.getData() != NULL){
                    packetR >> numberPlayersInt >> numberGoalsInt;
                    std::cout <<  numberPlayersInt << numberGoalsInt << std::endl;
                    break;
                }
            }
            first_run = true;
            maze = generatePlayingfield(numberPlayersInt);
            string mazeString = maze.print();
            std::cout << mazeString;
            packetS << mazeString;
            socket.send(packetS);
        }
        else{
            while(true){
                packetR.clear();
                socket.receive(packetR);
                if(packetR.getData() != NULL){
                    packetR >> turn >> new_ball_x >> new_ball_y;
                    std::cout <<  turn << std::endl;
                    break;
                }
            }
            if (turn == 1){
                //Pathfinding
                vector<vector<int>> sol;
                maze.at(old_ball_x)->at(old_ball_y)->name = "0";
                maze.at(new_ball_x)->at(new_ball_y)->name = "2";
                old_ball_x = new_ball_x;
                old_ball_y = new_ball_y;
                Pathfinder finder = Pathfinder();
                finder.setField(&maze);
                finder.setH();
                sol = finder.move();
                std::cout << "finding ended" << std::endl;
                string solString;
                for(vector<int> elements : sol){
                    solString += to_string(elements.at(0));
                    solString += to_string(elements.at(1));
                }
                std::cout << solString;
                packetS.clear();
                packetS << solString;
                socket.send(packetS);
            }
            else{
                //Backtracking 
                MatrixBP sol = MatrixBP();
                maze.at(old_ball_x)->at(old_ball_y)->name = "0";
                maze.at(new_ball_x)->at(new_ball_y)->name = "2";
                old_ball_x = new_ball_x;
                old_ball_y = new_ball_y;
                sol = generateCleanMatrix();
                sol = generateSolution(maze, sol, new_ball_y, new_ball_x);
                string solString = sol.print();
                std::cout << solString;
                packetS.clear();
                packetS << solString;
                socket.send(packetS);
            }
        }
    }
    
}

//Función que genera las posiciones aleatorias iniciales de los jugadores
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
        for(int x = 0; x <= 6; x++){
            for(int y = 0; y <= 2; y++){
                decide = random_num();
                if(decide == 50 && matrix.at(x)->at(y)->name == "0"){
                    matrix.at(x)->at(y)->name = "1";
                    placed += 1;
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
                    placed += 1;
                }
            }
        }
    }

    return matrix;
}

//función que genera un int aleatorio entre 1 y 100
int random_num(){
    int range = 100;
    int random_int = (rand() % range) + 1;
    return random_int;
}

//función que genera una matriz con solamente 0's
MatrixBP generateCleanMatrix(){
    MatrixBP matrix = MatrixBP();

    for(int i = 0; i <= 6; i++){
        ListBP list = ListBP();
        for(int j = 0; j <= 7; j++){
            list.append("0");
        }
        matrix.append(list);
    }

    return matrix;
}

//función que verifica si un cuadro es libre y parte de la matriz
bool check_safety(MatrixBP maze, int x, int y)
{
    if (x >= 0 && x < 7 && y >= 0 && y < 7 && maze.at(x)->at(y)->name != "1"){
        return true;
    }
    return false;
}
 
//función que genera la ruta más corta entre la bola y el gol del jugador por backtracking
MatrixBP generateSolution(MatrixBP maze, MatrixBP sol, int ball_x, int ball_y)
{
    std::cout << ball_x << ball_y << std::endl;
    if (generateSolution_aux(maze, ball_x, ball_y, sol) == false) {
        printf("Solution doesn't exist");
        return sol;
    }
    return sol;
}
 
//función auxiliar de generate solution, es la parte recursiva del backtracking
bool generateSolution_aux(MatrixBP maze, int x, int y, MatrixBP sol)
{
    // caso gol
    if (x == 3 && y == 0 && maze.at(x)->at(y)->name == "4") {
        sol.at(x)->at(y)->name = "1";
        return true;
    }
 
    if (check_safety(maze, x, y) == true) { 
        if (sol.at(x)->at(y)->name == "1"){
            return false;
        }
        sol.at(x)->at(y)->name = "1";

        //nos movemos un bloque hacia la izquierda
        if (generateSolution_aux(maze, x, y - 1, sol) == true){
            return true;
        }
 
        //nos movemos un bloque hacia abajo
        if (generateSolution_aux(maze, x + 1, y, sol) == true){
            return true;
        }
 
        //nos movemos un bloque hacia arriba
        if (generateSolution_aux(maze, x - 1, y, sol) == true){
            return true;
        }
 
        //nos movemos un bloque hacia la derecha
        if (generateSolution_aux(maze, x, y + 1, sol) == true){
            return true;
        }
       
        //si ninguna de las 4 direcciones sirve, significa que el bloque actual no pertenece a la solución
        sol.at(x)->at(y)->name = "0";
        return false;
    }
 
    return false;
}