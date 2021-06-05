#include <iostream>
#include <string.h>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "BP_GUI.h"
#include "Shoe.h"

BPGui::BPGui(){

    srand(time(NULL));

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
    ball.setPosition(400-(ball.getTextureRect().width/2),300-(ball.getTextureRect().height/2));

    //Creando menu para fuerza
    sf::RectangleShape forceMenu; 
    forceMenu.setPosition(200,250);
    forceMenu.setSize(sf::Vector2f(300.0f,200.0f));
    forceMenu.setFillColor(sf::Color(149, 165, 166 ));
    sf::RectangleShape forceNumber;
    sf::RectangleShape forceReady; 
    sf::Text forceNumberText;
    sf::Text forcePrompt,forceReadyText;
    forceNumberText.setFont(font);
    forcePrompt.setFont(font);
    forceReadyText.setFont(font);
    forceReady.setPosition(320,350);
    forceNumber.setPosition(260,350);
    forcePrompt.setPosition(250,270);
    forceReadyText.setPosition(330,345);
    forceNumberText.setPosition(265,345);
    forceNumber.setSize(sf::Vector2f(50.0f,50.0f));
    forceReady.setSize(sf::Vector2f(150.0f,50.0f));
    forceNumber.setFillColor(sf::Color::White);
    forceReady.setFillColor(sf::Color(46, 204, 113));
    forcePrompt.setFillColor(sf::Color::Black);
    forceReadyText.setFillColor(sf::Color::Black);
    forceNumberText.setFillColor(sf::Color::Black);
    forcePrompt.setString("Force: [1-3]");
    forceReadyText.setString("Ready?");
    forceNumberText.setString("0");
    forcePrompt.setCharacterSize(50);
    forceReadyText.setCharacterSize(50);
    forceNumberText.setCharacterSize(50);

    //Creando variables de forceMenu
    string forceNumberString = "0";
    ballPos.x = 3;
    ballPos.y = 3;
    

    //Creando Zapato para tirar 
    Shoe shoe = Shoe();

    //Creando text scores 
    sf::Text userScore, machineScore; 
    userScore.setFont(font);
    machineScore .setFont(font);
    userScore.setCharacterSize(60);
    machineScore.setCharacterSize(60);
    userScore.setFillColor(sf::Color::White);
    machineScore.setFillColor(sf::Color::White);
    userScore.setPosition(20,530);
    machineScore.setPosition(750,530);
    userScore.setString(to_string(userGoals));
    machineScore.setString(to_string(machineGoals));


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
                } else if(applyingForce){
                    if(!(event.text.unicode == 8)){
                        forceNumberString += event.text.unicode;
                    } else {
                        if(forceNumberString.length() > 0){
                            forceNumberString.pop_back();
                        }
                    }
                    forceNumberText.setString(forceNumberString);
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                sf::Vector2f mousePos(mouseX,mouseY);

                if(menuBool){
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

                            sf::TcpListener listener;
                            listener.listen(8080);
                            listener.accept(socket);

                            packetS << numberPlayersInt << numberGoalsInt;
                            socket.send(packetS);
                            

                            std::cout << "Sent" << std::endl;

                        
                            while(true){
                                socket.receive(packetR);
                                if(packetR.getData() != NULL){
                                    packetR >> matrixString;
                                    std::cout <<  matrixString << std::endl;
                                    break;
                                }
                            }

                            matrix = generateMatrixFrom(matrixString);
                            matrix.print();

                        } else{ 
                            tryAgainBool = true; 
                        }
                    }
                } else {
                    if(!applyingForce && isTurn){
                        applyingForce = true;
                        degreeWhenForce = shoe.getAngleDegree();
                    } else if(isTurn){
                        if(forceReady.getGlobalBounds().contains(mousePos)){
                            force = 0;
                            try{
                                force = std::stoi(forceNumberString);
                            } catch(std::exception e){
                                std::cout << "Could not load player and goal number" << std::endl;
                            }
                        }
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

        } else { //Dibujando Juego (agregar if isTurn)
            
            if (isTurn){
                applyForceBall(&window,&userScore,&machineScore);
            
                userScore.setFillColor(sf::Color(231, 76, 60));
                machineScore.setFillColor(sf::Color::White);

                drawFromMatrix(&window,&matrix);
                window.draw(ball);
                window.draw(*shoe.getFoot());
                window.draw(userScore);
                window.draw(machineScore);
                
                if(applyingForce){
                    window.draw(forceMenu);
                    window.draw(forceNumber);
                    window.draw(forcePrompt);
                    window.draw(forceReady);
                    window.draw(forceReadyText);
                    window.draw(forceNumberText);
                } else {
                    if(force < 1){
                        //get pathfinding
                        //packetS.clear();
                        //packetS << 1 << ballPos.x << ballPos.y;
                        //socket.send(packetS);

                        drawFromMatrix(&window,&matrix);
                        window.draw(ball);
                        window.draw(userScore);
                        window.draw(machineScore);
                    }
                }
            } else{ 

                std::cout << "Not turn"<< std::endl;

                //get backtracking 
                packetS.clear();
                packetS << 2 << ballPos.x << ballPos.y;
                socket.send(packetS);

                
                string backtrackString;
                packetR.clear();
                
                while(true){
                    socket.receive(packetR);
                    if(packetR.getData() != NULL){
                        packetR >> backtrackString;
                        std::cout <<  backtrackString << std::endl;
                        break;
                    }
                }

                MatrixBP backtrackMatrix;
                backtrackMatrix = generateMatrixFrom(backtrackString);
                backtrackMatrix.print();

                moveFrom(backtrackMatrix,&window,&userScore,&machineScore);

                machineScore.setFillColor(sf::Color(231, 76, 60));
                userScore.setFillColor(sf::Color::White);
                drawFromMatrix(&window,&matrix);
                window.draw(ball);
                window.draw(userScore);
                window.draw(machineScore);

            }
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

void BPGui::showPathfinderFrom(vector<vector<int>> path,sf::RenderWindow* window){
    sf::Sprite newBall = ball;
    newBall.setColor(sf::Color(255,255,255,128));
    for(vector<int> elements : path){
        newBall.setPosition(
            ((window->getSize().x/matrix.at(elements.at(1))->getLength())*elements .at(0)) + 37,
            (((window->getSize().y-50)/matrix.getLength())*elements .at(1)) + 26
        );
        window->draw(newBall);
    }
}
void BPGui::moveFrom(
    MatrixBP backtrackingMatrix,
    sf::RenderWindow* window,
    sf::Text* userScore, 
    sf::Text* machineScore
    ){

    sf::Sprite newBall = ball;
    newBall.setColor(sf::Color(255,255,255,128));
    int newX;
    int newY;
    for(int i = 0; i < backtrackingMatrix.getLength(); i++){
        ListBP* newList = backtrackingMatrix.at(i);
        for(int j = 0; j < newList->getLength();j++){
            NodeBPG* newNode = newList->at(j);
            if(newNode->name == "1"){
                if(abs(i-ballPos.y) == 1 && abs(j-ballPos.x) == 1){
                    newX = j;
                    newY = i;
                }
                newBall.setPosition(
                    ((window->getSize().x/matrix.at(i)->getLength())*j) + 37,
                    (((window->getSize().y-50)/matrix.getLength())*i) + 26
                );
                window->draw(newBall);
            }
        }
    }
    sleep(1);
    //añadir casos para degreeAngle
    if(ballPos.y-newY > 0){
        degreeWhenForce = 270;
    } else if(ballPos.y - newY < 0){
        degreeWhenForce = 90;
    } else if(ballPos.x - newX > 0){
        degreeWhenForce = 180;
    } else if(ballPos.x = newX < 0){ 
        degreeWhenForce = 0;
    }
    force = random_num();
    while(force > 0){
        applyForceBall(window,userScore,machineScore);
    }
}

void BPGui::applyForceBall(sf::RenderWindow* window, sf::Text* userScore, sf::Text* machineScore){
    if(force >  0 && force <= 3){
        applyingForce = false;
        if(force > 0){
            if(
                (degreeWhenForce >= 0 && degreeWhenForce <= 30) ||
                (degreeWhenForce >= 330 && degreeWhenForce <=  360)
            ){
                //Hacia izquierda
                if(
                    ballPos.x-1 >= 0 &&
                    matrix.at(ballPos.y)->at(ballPos.x-1)->name != "1"
                ){
                    ballPos.x--;
                }       
            } else if(
                (degreeWhenForce >= 150 && degreeWhenForce <= 180) ||
                (degreeWhenForce >= 180 && degreeWhenForce <=  210)
            ){
                //Hacia derecha
                if(
                    ballPos.x+1 < matrix.at(ballPos.y)->getLength() &&
                    matrix.at(ballPos.y)->at(ballPos.x+1)->name != "1"
                ){
                    ballPos.x++;
                }
            } else if(
                (degreeWhenForce >= 60 && degreeWhenForce <= 90) ||
                (degreeWhenForce >= 90 && degreeWhenForce <=  120)
            ){
                //Hacia  abajo
                if(
                    ballPos.y+1 < matrix.getLength() &&
                    matrix.at(ballPos.y+1)->at(ballPos.x)->name != "1"
                ){
                    ballPos.y++;
                }
            } else if(
                (degreeWhenForce >= 240 && degreeWhenForce <= 270) ||
                (degreeWhenForce >= 270 && degreeWhenForce <=  300)
            ){
                //Hacia  arriba
                if(
                    ballPos.y-1 >= 0 &&
                    matrix.at(ballPos.y-1)->at(ballPos.x)->name != "1"
                ){
                    ballPos.y--;
                }
            } else if(degreeWhenForce > 30 && degreeWhenForce < 60){
                //SurOeste
                if(
                    ballPos.x-1 >= 0 &&
                    ballPos.y+1 < matrix.getLength() && 
                    matrix.at(ballPos.y+1)->at(ballPos.x-1)->name != "1"
                ){
                    ballPos.y++;
                    ballPos.x--;
                }
            } else if(degreeWhenForce > 120 && degreeWhenForce < 150){
                //SurEste
                if(
                    ballPos.x+1 < matrix.at(ballPos.y)->getLength() &&
                    ballPos.y+1 < matrix.getLength() && 
                    matrix.at(ballPos.y+1)->at(ballPos.x+1)->name != "1"
                ){
                    ballPos.y++;
                    ballPos.x++;
                }
            } else if(degreeWhenForce > 210 && degreeWhenForce < 240){
                //Noreste
                if(
                    ballPos.y-1 >= 0 &&
                    ballPos.x+1 < matrix.at(ballPos.y)->getLength() && 
                    matrix.at(ballPos.y-1)->at(ballPos.x+1)->name != "1"
                ){
                    ballPos.y--;
                    ballPos.x++;
                }
            } else if(degreeWhenForce > 300 && degreeWhenForce < 330){
                //SurOeste
                if(
                    ballPos.y-1 >= 0 &&
                    ballPos.x-1 >= 0 && 
                    matrix.at(ballPos.y-1)->at(ballPos.x-1)->name != "1"
                ){
                    ballPos.y--;
                    ballPos.x--;
                }
            }
            if(matrix.at(ballPos.y)->at(ballPos.x)->name == "3"){
                userGoals++;
                userScore->setString(to_string(userGoals));
                ballPos.x = 3; ballPos.y = 3; force = 0;
                isTurn = !isTurn;
            } else if(matrix.at(ballPos.y)->at(ballPos.x)->name == "4"){
                machineGoals++;
                machineScore->setString(to_string(machineGoals));
                ballPos.x = 3; ballPos.y = 3; force = 0;
                isTurn = !isTurn;
            }
            ball.setPosition(
                ((window->getSize().x/matrix.at(ballPos.y)->getLength())*ballPos.x) + 37,
                (((window->getSize().y-50)/matrix.getLength())*ballPos.y) + 26
            );
            sleep(0.5);
            force--;
            if(force == 0){
                std::cout << "Changed turn!" << std::endl;
                isTurn = !isTurn;
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

     //Sprite Bola 
    if(!ballTexture.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/Img/Ball.png")){
        std::cout << "Image not loaded" << std::endl;
    }
    ball.setTexture(ballTexture);
}

MatrixBP BPGui::generateMatrixFrom(string matrixString){
    MatrixBP matrix = MatrixBP();

    for(int i = 0; i <= 6; i++){
        ListBP list = ListBP();
        for(int j = 0; j <= 7; j++){
            string s;
            char c; 
            c = matrixString[j+(8*i)];
            s += c;
            std::cout << ((j+(8*i))+1) % 8 << " ";
            if(((j+(8*i))+1) % 8 > 0){
                list.append(s);
            }
        }
        std::cout << std::endl;
        matrix.append(list);
    }

    return matrix;
}

int BPGui::random_num(){
    int range = 3;
    int random_int = (rand() % range) + 1;
    return random_int;
}