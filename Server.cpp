#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "Matrix_BP.h"
#include "List_BP.h"
#include "Pathfinder.h"
#include "GeneticAlgorithm.h"
#include "BP_GUI.h"

/**
 * @file Server.cpp
 * @version 1.0
 * @title Server
 * @brief maneja la logica de los algoritmos y se contacta con cliente por sockets
 */

using namespace sf;
using namespace std;

MatrixBP generateCleanMatrix();
MatrixBP generatePlayingfield(int players);
int random_num();
MatrixBP generateSolution(MatrixBP maze, MatrixBP sol, int ball_x, int ball_y);
bool generateSolution_aux(MatrixBP maze, int x, int y, MatrixBP sol);
bool check_safety(MatrixBP maze, int x, int y);

/**
 * @brief main de server, se encarga de la logica de los algoritmos
 * */
int main(){
    
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);
    sf::Packet packetS, packetR;

    int mode = - 1; 
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

     while(true){
        packetR.clear();
        socket.receive(packetR);
        if(packetR.getData() != NULL){
            packetR >> mode;
            std::cout << mode << std::endl;
            break;
        }
    }

    while (running){
        if(mode == 0){
            if (first_run != true){
                while(true){
                    packetR.clear();
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
                        std::cout <<  turn << new_ball_x << new_ball_y << std::endl;
                        break;
                    }
                }
                if (turn == 1){
                    //Pathfinding
                    vector<vector<int>> sol;
                    maze.at(old_ball_y)->at(old_ball_x)->name = "0";
                    maze.at(new_ball_y)->at(new_ball_x)->name = "2";
                    old_ball_x = new_ball_x;
                    old_ball_y = new_ball_y;
                    string mazeString = maze.print();
                    MatrixBP newMatrix = BPGui::generateMatrixFrom(mazeString);
                    Pathfinder finder; 
                    finder.setField(&newMatrix);
                    finder.setH();
                    sol = finder.move();

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
                    maze.at(old_ball_y)->at(old_ball_x)->name = "0";
                    maze.at(new_ball_y)->at(new_ball_x)->name = "2";
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
        } else if(mode == 1){
            string image;
            int numPieces = 0;
            bool primo = false;

            while (true)
            {
                packetR.clear();
                socket.receive(packetR);
                if (packetR.getData() != NULL)
                {
                    packetR >> image >> numPieces >> primo;
                    cout << image << " - " << numPieces << endl;
                    break;
                }
            }
            GeneticAlgorithm solver(image, numPieces, primo);
        } else {
            while(true){
                packetR.clear();
                socket.receive(packetR);
                if(packetR.getData() != NULL){
                    packetR >> mode;
                    std::cout << mode << std::endl;
                    break;
                }
            }
        }
        
    }
    
}

/**
 * @brief Función que genera las posiciones aleatorias iniciales de los jugadores
 * @param int players numero de jugadores a crear
 * @return MatrixBP matriz con los jugadores creados (nodos con nombre 1)
 **/
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

/**
 * @brief función que genera una matriz con solamente 0's
 **/
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

/**
 * @brief función que verifica si un cuadro es libre y parte de la matriz
 * @param MatrixBP maze matriz para verificacion
 * @param int x posicion x a revisar
 * @param int y posicion y a revisar
 * @return bool si ek cuadro es libre y seguro
 **/ 
bool check_safety(MatrixBP maze, int x, int y)
{
    if (x >= 0 && x < 7 && y >= 0 && y < 7 && maze.at(x)->at(y)->name != "1"){
        return true;
    }
    return false;
}
 
/**
 * @brief función que genera la ruta más corta entre la bola y el gol del jugador por backtracking
 * @param MatrixBP maze matriz a revisar
 * @param MatrixBP sol matriz donde se guarda la solucion
 * @param int ball_x posicion x de la bola 
 * @param int ball_y posicion y de la bola 
 * @return MatrixBP matriz donde se indica ruta por medio de unos
 **/
MatrixBP generateSolution(MatrixBP maze, MatrixBP sol, int ball_x, int ball_y)
{
    std::cout << ball_x << ball_y << std::endl;
    if (generateSolution_aux(maze, ball_x, ball_y, sol) == false) {
        printf("Solution doesn't exist");
        return sol;
    }
    return sol;
}
 
/**
 * @brief función auxiliar de generate solution, es la parte recursiva del backtracking
 **/
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
