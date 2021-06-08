#include <SFML/Graphics.hpp>
#include <iostream>
#include "BP_GUI.h"
#include "geneticPuzzle.h"

/**
 * @file Menu.cpp
 * @version 1.0
 * @title Menu
 * @brief Manejo de ingreso a BP Game y GP
 */

/**
 * @brief funcion main, crea menu para escoger entre BP Game y GP
 * */
int main(){

    sf::RenderWindow window(sf::VideoMode(600, 600), "Let's Play!");

    //Buttons
    sf::RectangleShape buttonBP; //Button BP GAME
    sf::RectangleShape buttonGP; //BUtton Genetic Puzzle

    buttonBP.setPosition(100,120);
    buttonBP.setSize(sf::Vector2f (400, 120));
    sf::Color idleColor = sf::Color::Blue;
    sf::Color activeColor = sf::Color::Green;
    buttonBP.setFillColor(idleColor);
    buttonGP.setPosition(100, 360);
    buttonGP.setSize(sf::Vector2f (400, 120));
    sf::Color idleColor2 = sf::Color::Red;
    sf::Color activeColor2 = sf::Color::Blue;
    buttonGP.setFillColor(idleColor2);

    //font
    sf::Font font;
    if (!font.loadFromFile("/home/jose430/Documents/Proyecto-2-Datos-2/retro.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }

    //Text
    sf::Text textButtonBP, textButtonGP;
    textButtonBP.setString("BP Game");
    textButtonBP.setFillColor(sf::Color::White);
    textButtonBP.setCharacterSize(70);
    textButtonBP.setPosition(120,125);
    textButtonBP.setFont(font);

    textButtonGP.setString("Genetic Puzzle");
    textButtonGP.setFillColor(sf::Color::White);
    textButtonGP.setCharacterSize(70);
    textButtonGP.setPosition(120,365);
    textButtonGP.setFont(font);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                
                float mouseX = event.mouseButton.x;
                float mouseY = event.mouseButton.y;
                sf::Vector2f mousePos(mouseX,mouseY);
                
                if (buttonBP.getGlobalBounds().contains(mousePos)){
                    //send mode 0

                    window.setActive(false);
                    window.setVisible(false);
                    BPGui* newGui = new BPGui();
                    window.setVisible(true);
                    window.setActive(true);
                }
                
                else if (buttonGP.getGlobalBounds().contains(mousePos)){
                    //send mode 1

                    std::cout << "Genetic Puzzle!" << std::endl;
                    window.setActive(false);
                    window.setVisible(false);
                    geneticPuzzle();
                    window.setVisible(true);
                    window.setActive(true);
                }
            }
        }

        window.clear();
        window.draw(buttonGP);
        window.draw(buttonBP);
        window.draw(textButtonBP);
        window.draw(textButtonGP);
        window.display();
        
    }
    
    return 0;
}