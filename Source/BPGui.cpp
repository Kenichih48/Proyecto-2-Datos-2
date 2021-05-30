#include "BP_GUI.h"
#include <iostream>
#include <string.h>

BPGui::BPGui(){
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
    numberPlayersString = "0";
    numberGoalsString = "0";
    numberPlayers.setFont(font);
    numberGoals.setFont(font);
    playersPrompt.setFont(font);
    goalsPrompt.setFont(font);
    playersButtonText.setFont(font);
    goalsButtonText.setFont(font);
    goalsPrompt.setPosition(120,265);
    playersPrompt.setPosition(120,105);
    numberPlayers.setPosition(125,195);
    numberGoals.setPosition(125,345);
    playersButtonText.setPosition(360,188);
    goalsButtonText.setPosition(360,338);
    numberPlayers.setString(numberPlayersString);
    numberGoals.setString(numberGoalsString);
    playersPrompt.setString("Number of Players:");
    goalsPrompt.setString("Number of Goals:");
    playersButtonText.setString("Edit");
    goalsButtonText.setString("Edit");
    numberPlayers.setFillColor(sf::Color::Black);
    numberGoals.setFillColor(sf::Color::Black);
    playersPrompt.setFillColor(sf::Color::White);
    goalsPrompt.setFillColor(sf::Color::White);
    playersButtonText.setFillColor(sf::Color::Black);
    goalsButtonText.setFillColor(sf::Color::Black);
    numberPlayers.setCharacterSize(50);
    numberGoals.setCharacterSize(50);
    playersPrompt.setCharacterSize(50);
    goalsPrompt.setCharacterSize(50);
    playersButtonText.setCharacterSize(50);
    goalsButtonText.setCharacterSize(50);

    //Creando Botones para Menu
    sf::RectangleShape numberPlayersButton, numberGoalsButton;
    numberPlayersButton.setFillColor(sf::Color(231, 76, 60));
    numberGoalsButton.setFillColor(sf::Color(231, 76, 60));
    numberPlayersButton.setPosition(300,195);
    numberGoalsButton.setPosition(300,345);
    numberPlayersButton.setSize(sf::Vector2f(200.0f,50.0f));
    numberGoalsButton.setSize(sf::Vector2f(200.0f,50.0f));

    //Creando Bools para menu 
    bool menuBool = true;
    bool numberPlayersBool = false; 
    bool numberGoalsBool = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::TextEntered){
                if(numberPlayersBool){
                    numberPlayersString += event.text.unicode;
                    numberPlayers.setString(numberPlayersString);
                } else if (numberGoalsBool){
                    numberGoalsString += event.text.unicode;
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
        }
        
        window.display();
    }

}