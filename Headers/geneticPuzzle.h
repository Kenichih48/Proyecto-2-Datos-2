#ifndef GENETICPUZZLE_H_
#define GENETICPUZZLE_H_ 


#include <SFML/Network.hpp>
#include <iostream>
#include "ListGP.h"
#include "MatrixGP.h"


using namespace sf;
using namespace std;

///Main program
int geneticPuzzle() //int argc, char const *argv[]
{
    Packet packetS, packetR;
    int numPieces;
    bool primo = false;
    string image;
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    ListGP<MatrixGP<int>*>* matrixes;

    socket.connect(ip, 8080);

    packetS << 1;
    socket.send(packetS);

    cout << "Genetic Puzzle\n" << endl;
    cout << "Please enter the name of the image file: " << endl;
    cin >> image;
    cout << "Enter the amount of pieces for the puzzle:" << endl;
    cin >> numPieces;

    while (!primo) {
        int divider = 1, dividers = 0;
        do {
            if (numPieces % divider == 0)
                dividers++;
            divider++;
        } while (divider <= numPieces);

        if (dividers == 2) {
            primo = true;
        }
        break;
    }
    packetS.clear();
    packetS << image << numPieces << primo;
    socket.send(packetS);

    return 0;
}

#endif /* GENETICPUZZLE_H_ */