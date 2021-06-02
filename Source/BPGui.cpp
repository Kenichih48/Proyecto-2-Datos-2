#include <iostream>
#include <string.h>
#include <SFML/Network.hpp>
#include "BP_GUI.h"
#include "Shoe.h"

BPGui::BPGui(){

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    sf::Packet packetS, packetR;
    socket.connect(ip, 8080);

    sf::RenderWindow window(sf::VideoMode(800, 600), "BP Game");
    
    //Cargando Fondo
    sf::Texture field; 
    if(!field.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/Img/field.png")){
        std::cout << "Image not loaded" << std::endl;
    }
    sf::Sprite background; 
    background.setTexture(field);
    background.setPosition(0,0);

    //Creacion de Menu para ingresar numero jugadores y goles
    sf::RectangleShape menu; 
    menu.setPosition(100,100);
    menu.setSize(sf::Vector2f(600.0f,400.0f));
    menu.setFillColor(sf::Color(149, 165, 166 ));
    sf::RectangleShape numberPlayersRect;
    sf::RectangleShape numberGoalsRect; 
    numberPlayersRect.setPosition(120,195);
    numberGoalsRect.setPosition(120,345);
    numberPlayersRect.setSize(sf::Vector2f(100.0f,50.0f));
    numberGoalsRect.setSize(sf::Vector2f(100.0f,50.0f));

    //Creando Font
    sf::Font font;
    if (!font.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/retro.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }

    //Creando textos menu
    std::string numberPlayersString, numberGoalsString;
    sf::Text numberPlayers, numberGoals;
    sf::Text playersPrompt, goalsPrompt;
    sf::Text playersButtonText, goalsButtonText;
    sf::Text ready, tryAgain;
    numberPlayersString = "0";
    numberGoalsString = "0";
    numberPlayers.setFont(font);
    numberGoals.setFont(font);
    playersPrompt.setFont(font);
    goalsPrompt.setFont(font);
    playersButtonText.setFont(font);
    goalsButtonText.setFont(font);
    ready.setFont(font);
    tryAgain.setFont(font);
    goalsPrompt.setPosition(120,265);
    playersPrompt.setPosition(120,105);
    numberPlayers.setPosition(125,195);
    numberGoals.setPosition(125,345);
    playersButtonText.setPosition(360,188);
    goalsButtonText.setPosition(360,338);
    ready.setPosition(340,425);
    tryAgain.setPosition(510,425);
    numberPlayers.setString(numberPlayersString);
    numberGoals.setString(numberGoalsString);
    playersPrompt.setString("Number of Players: (1-12)");
    goalsPrompt.setString("Number of Goals: (1-10)");
    playersButtonText.setString("Edit");
    goalsButtonText.setString("Edit");
    ready.setString("Ready!");
    tryAgain.setString("Try Again");
    numberPlayers.setFillColor(sf::Color::Black);
    numberGoals.setFillColor(sf::Color::Black);
    playersPrompt.setFillColor(sf::Color::White);
    goalsPrompt.setFillColor(sf::Color::White);
    playersButtonText.setFillColor(sf::Color::Black);
    goalsButtonText.setFillColor(sf::Color::Black);
    ready.setFillColor(sf::Color::Black);
    tryAgain.setFillColor(sf::Color::Black);
    numberPlayers.setCharacterSize(50);
    numberGoals.setCharacterSize(50);
    playersPrompt.setCharacterSize(50);
    goalsPrompt.setCharacterSize(50);
    playersButtonText.setCharacterSize(50);
    goalsButtonText.setCharacterSize(50);
    ready.setCharacterSize(50);
    tryAgain.setCharacterSize(50);

    //Creando Botones para Menu
    sf::RectangleShape numberPlayersButton, numberGoalsButton;
    sf::RectangleShape readyButton;
    numberPlayersButton.setFillColor(sf::Color(231, 76, 60));
    numberGoalsButton.setFillColor(sf::Color(231, 76, 60));
    readyButton.setFillColor(sf::Color(46, 204, 113));
    numberPlayersButton.setPosition(300,195);
    numberGoalsButton.setPosition(300,345);
    readyButton.setPosition(300,435);
    numberPlayersButton.setSize(sf::Vector2f(200.0f,50.0f));
    numberGoalsButton.setSize(sf::Vector2f(200.0f,50.0f));
    readyButton.setSize(sf::Vector2f(200.0f,50.0f));

    //Creando Bools para menu 
    bool menuBool = true;
    bool numberPlayersBool = false; 
    bool numberGoalsBool = false;
    bool tryAgainBool = false; 

    //Creado Sprites Juego 
    setUpSprites();
    sf::Texture ballTexture; //Sprite Bola 
    if(!ballTexture.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/Img/Ball.png")){
        std::cout << "Image not loaded" << std::endl;
    }
    sf::Sprite ball; 
    ball.setTexture(ballTexture);
    ball.setPosition(400-(ball.getTextureRect().width/2),300-(ball.getTextureRect().height/2));

    //Creando menu para fuerza
     sf::RectangleShape forceMenu; 
    menu.setPosition(200,250);
    menu.setSize(sf::Vector2f(300.0f,200.0f));
    menu.setFillColor(sf::Color(149, 165, 166 ));
    sf::RectangleShape forceNumber;
    sf::RectangleShape forceReady; 
    sf::Text forcePrompt,forceReadyText;
    forceReady.setPosition(350,400);
    forceNumber.setPosition(300,400);
    forcePrompt.setPosition(250,270);
    numberPlayersRect.setSize(sf::Vector2f(50.0f,50.0f));
    numberGoalsRect.setSize(sf::Vector2f(50.0f,50.0f));
    forceNumber.setFillColor(sf::Color::White);
    forceReady.setFillColor(sf::Color(46, 204, 113));
    forcePrompt.setFillColor(sf::Color::White);
    forcePrompt.setString("Force [1-10]");
    forcePrompt.setString("Ready?");

    //Creando Zapato para tirar 
    Shoe shoe = Shoe();

    //Creando Matriz de ejemplo
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
    matrix2->at(0)->at(2)->name = "1";
    matrix2->at(3)->at(2)->name = "1";
    matrix2->at(2)->at(4)->name = "1";
    matrix2->at(5)->at(4)->name = "1";
    matrix2->at(1)->at(5)->name = "1";
    matrix2->at(3)->at(5)->name = "1";
    matrix2->at(5)->at(6)->name = "1";
    matrix2->at(3)->at(6)->name = "3"; 
    
    matrix2->print();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseMoved){
                sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                shoe.rotateShoe(&ball, mousePos);
            }
            if(event.type == sf::Event::TextEntered){
                if(numberPlayersBool){
                    if(!(event.text.unicode == 8)){
                        numberPlayersString += event.text.unicode;
                    } else {
                        if(numberPlayersString.length() > 0){
                            numberPlayersString.pop_back();
                        }
                    }
                    numberPlayers.setString(numberPlayersString);
                } else if (numberGoalsBool){
                    if(!(event.text.unicode == 8)){
                        numberGoalsString += event.text.unicode;
                    } else {
                        if(numberGoalsString.length() > 0){
                            numberGoalsString.pop_back();
                        }
                    }
                    numberGoals.setString(numberGoalsString);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                sf::Vector2f mousePos(mouseX,mouseY);

                if (numberPlayersButton.getGlobalBounds().contains(mousePos)){
                    if(!numberPlayersBool){
                        numberPlayersBool = true; 
                        numberPlayersButton.setFillColor(sf::Color(46, 204, 113));
                        playersButtonText.setString("Done?");
                    } else {
                        numberPlayersBool = false; 
                        numberPlayersButton.setFillColor(sf::Color(231, 76, 60));
                        playersButtonText.setString("Edit");
                    }
                }

                else if (numberGoalsButton.getGlobalBounds().contains(mousePos)){
                    if(!numberGoalsBool){
                        numberGoalsBool = true; 
                        numberGoalsButton.setFillColor(sf::Color(46, 204, 113));
                        goalsButtonText.setString("Done?");
                    } else {
                        numberGoalsBool = false; 
                        numberGoalsButton.setFillColor(sf::Color(231, 76, 60));
                        goalsButtonText.setString("Edit");
                    }
                }

                else if(readyButton.getGlobalBounds().contains(mousePos)){
                    int numberPlayersInt = 0;
                    int numberGoalsInt = 0;
                    std::string playerSTDString = numberPlayers.getString();
                    std::string goalsSTDString = numberGoals.getString();
                    try{
                        numberPlayersInt = std::stoi(playerSTDString);
                        numberGoalsInt = std::stoi(goalsSTDString);
                    } catch(std::exception e){
                        std::cout << "Could not load player and goal number" << std::endl;
                    }
                    if((numberPlayersInt > 0 && numberPlayersInt <= 12)
                    &&(numberGoalsInt > 0 && numberGoalsInt <= 10)){
                        menuBool = false; 

                        packetS << numberPlayersInt << numberGoalsInt;
                        socket.send(packetS);

                    } else{ 
                        tryAgainBool = true; 
                    }
                }
            }
        }
        window.clear();

        //Dibujando fondo
        window.draw(background);

        //Dibujando menu jugadores goles
        if(menuBool){
            window.draw(menu);
            window.draw(numberPlayersRect);
            window.draw(numberGoalsRect);
            window.draw(numberPlayersButton);
            window.draw(numberGoalsButton);
            window.draw(playersButtonText);
            window.draw(goalsButtonText);
            window.draw(playersPrompt);
            window.draw(numberPlayers);
            window.draw(goalsPrompt);
            window.draw(numberGoals);
            window.draw(readyButton);
            window.draw(ready);
            if(tryAgainBool){
                window.draw(tryAgain);
            }

        } else { //Dibujando Juego
            drawFromMatrix(&window,matrix2);
            window.draw(ball);
            window.draw(*shoe.getFoot());
        }

        window.display();
    }

}

void BPGui::drawFromMatrix(sf::RenderWindow* window, MatrixBP* matrix){
    int x = 0; 
    int y = 0;
    for(int i = 0; i < matrix->getLength();i++){
        ListBP* newList = matrix->at(i);
        for(int j = 0; j < newList->getLength(); j++){
            NodeBPG* newNode = newList->at(j);
            if(newNode->name == "1"){
                sf::Sprite newPlayer;
                if(j < ((int)newList->getLength()/2)){
                    newPlayer = user;    
                } else{ 
                    newPlayer = machine;
                }
                
                newPlayer.setPosition(
                    ((int)(window->getSize().x/newList->getLength()) *j)+15,
                    ((int)((window->getSize().y-50)/matrix->getLength()) *i)-10
                );
                window->draw(newPlayer);
            }
        }
    }
}

void BPGui::setUpSprites(){
    if(!players.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/Img/FootballPlayers.png")){
        std::cout << "Image not loaded" << std::endl;
    }
    user.setTexture(players);
    machine.setTexture(players);
    user.setTextureRect(sf::IntRect(0,0,77,85));
    machine.setTextureRect(sf::IntRect(0,85,77,170));
}