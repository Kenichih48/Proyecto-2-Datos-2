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
    string image, numPiecesStr, okStr;
    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    ListGP<MatrixGP<int>*>* matrixes;
    bool name, pieces;
    Text imageText, numPiecesText, okText;
    RectangleShape imageBackground, numPiecesBackground, background, ok;
    Texture backgroundTexture;
    Font font;
    font.loadFromFile("Ubuntu-M.ttf");

    imageText.setFont(font);
    imageText.setCharacterSize(15);
    imageText.setFillColor(Color::White);
    imageText.setPosition(30,70);
    imageBackground.setFillColor(Color::Black);
    imageBackground.setSize(Vector2f(370,50));
    imageBackground.setPosition(25,90);

    numPiecesText.setFont(font);
    numPiecesText.setCharacterSize(15);
    numPiecesText.setFillColor(Color::White);
    numPiecesText.setPosition(30,200);
    numPiecesBackground.setFillColor(Color::Black);
    numPiecesBackground.setSize(Vector2f(370,50));
    numPiecesBackground.setPosition(25,220);

    okStr = "DONE";
    okText.setString(okStr);
    okText.setFont(font);
    okText.setCharacterSize(30);
    okText.setFillColor(Color::Black);
    okText.setPosition(170,330);
    ok.setFillColor(Color::Green);
    ok.setSize(Vector2f(150,50));
    ok.setPosition(135,320);

    backgroundTexture.loadFromFile("Img/Background.png");
    background.setPosition(0,0);
    background.setTexture(&backgroundTexture);
    background.setSize(Vector2f(420, 627));

    socket.connect(ip, 8080);

    packetS << 1;
    socket.send(packetS);

    RenderWindow window(VideoMode(420,627,32), "Genetic Puzzle");
    window.setVerticalSyncEnabled(true);
    font.loadFromFile("Ubuntu-M.ttf");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (imageBackground.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && !name){
                        name = true;
                        pieces = false;
                    }
                    else if (numPiecesBackground.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && !pieces){
                        pieces = true;
                        name = false;
                    }
                    else if (ok.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        window.close();
                }
            }
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
            if (event.type == Event::TextEntered) {
                if (name) {
                    if (event.text.unicode == 13)
                        name = false;
                    else if (event.text.unicode != 8)
                        image += event.text.unicode;
                    else {
                        if (image.length() > 0)
                            image.pop_back();
                    }
                } else if (pieces) {
                    if (event.text.unicode == 13)
                        pieces = false;
                    else if (event.text.unicode != 8)
                        numPiecesStr += event.text.unicode;
                    else {
                        if (numPiecesStr.length() > 0)
                            numPiecesStr.pop_back();
                    }
                }
            }
        }

        imageText.setString("Please enter the name of the image file:\n\n        " + image);
        numPiecesText.setString("Enter the amount of pieces for the puzzle:\n\n                                         "
                                + numPiecesStr);

        window.draw(background);
        window.draw(imageBackground);
        window.draw(numPiecesBackground);
        window.draw(ok);
        window.draw(okText);
        window.draw(imageText);
        window.draw(numPiecesText);
        window.display();

    }


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
    numPieces = stoi(numPiecesStr);
    packetS.clear();
    packetS << image << numPieces << primo;
    socket.send(packetS);

    return 0;
}

#endif /* GENETICPUZZLE_H_ */
