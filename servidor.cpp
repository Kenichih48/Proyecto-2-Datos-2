#include <SFML/Network.hpp>
#include "GeneticAlgorithm.h"
#include <iostream>

using namespace sf;
using namespace std;

///Main program
int main(int argc, char const *argv[])
{
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    TcpListener listener;
    listener.listen(8080);
    listener.accept(socket);

    Packet packetS, packetR;
    string image;
    int numPieces = 0;
    bool primo = false;

    while (true)
    {
        socket.receive(packetR);
        if (packetR.getData() != NULL)
        {
            packetR >> image >> numPieces >> primo;
            cout << image << " - " << numPieces << endl;
            break;
        }
    }
    GeneticAlgorithm solver(image, numPieces, primo);
}