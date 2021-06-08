#include "Shoe.h"
#include <iostream>
#include <math.h>

/**
 * @brief contructor de shoe, carga imagen del sprite 
 **/
Shoe::Shoe(){
    if(!shoeTexture.loadFromFile("Img/SoccerFoot.png")){
        std::cout << "Image not loaded" << std::endl;
    }
    foot.setTexture(shoeTexture);
    foot.setPosition(100,100);
}

/**
 * @brief cambia la rotacion y posicion del zapato con respecto a la diferencia de posicion de la bola y la posicion del mouse
 * @param sf::Sprite* bola 
 * @param sf::Vector2f mousePosition
 **/
void Shoe::rotateShoe(sf::Sprite* ball,sf::Vector2f mousePosition){
    bool isDown = mouseIsDown(*ball,mousePosition);
    float legX = abs(ball->getPosition().x+(ball->getTextureRect().width/2)-mousePosition.x);
    float legY = abs(ball->getPosition().y+(ball->getTextureRect().height/2)-mousePosition.y);
    float hypotenuse = sqrt(pow(legX,2) + pow(legY,2));
    angleDegree = 0;
    int differenceX;
    int differenceY;
    float radius = ball->getTextureRect().width/2;

    if(mouseIsRight(*ball, mousePosition)){
        if(flipped){
            flip();
        }
        if(isDown){
            double angleRadian = asin(legX/hypotenuse);
            angleDegree = angleRadian*(180/M_PI);
            angleDegree += 270;

            differenceX = (sin(angleDegree) * radius);
            differenceY = (cos(angleDegree) * radius);
        } else {
            double angleRadian = asin(legY/hypotenuse);
            angleDegree = angleRadian*(180/M_PI);

            differenceX = (cos(angleDegree) * radius);
            differenceY = (sin(angleDegree) * -radius) - foot.getTextureRect().height;

        }
    } else{
        if(!flipped){
            flip();
        }
        if(isDown){
            double angleRadian = asin(legY/hypotenuse);
            angleDegree = angleRadian*(180/M_PI);
            angleDegree +=  180;

            differenceX = (cos(angleDegree) * -radius);
            differenceY = (sin(angleDegree) * radius);
        } else {
            double angleRadian = asin(legX/hypotenuse);
            angleDegree = angleRadian*(180/M_PI);
            angleDegree += 90;

            differenceX = (sin(angleDegree) * -radius);
            differenceY = (cos(angleDegree) * -radius) - foot.getTextureRect().height;
        }
    }
    
    foot.setRotation(360 - angleDegree);

    int newX = (ball->getPosition().x+(ball->getTextureRect().width/2)) + differenceX;
    int newY = (ball->getPosition().y+(ball->getTextureRect().height/2)) + differenceY;

    foot.setPosition(newX,newY);

}

/**
 * @brief funcion para saber si el mouse esta a la derecha de la bola
 * @param sf::Sprite* bola 
 * @param sf::Vector2f mousePosition
 * @return bool si mouse esta a la derecha de la bola
 **/ 
bool Shoe::mouseIsRight(sf::Sprite ball,sf::Vector2f mousePosition){
    return mousePosition.x > ball.getPosition().x+(ball.getTextureRect().width/2);
}

/**
 * @brief funcion para saber si el mouse esta abajo de la bola
 * @param sf::Sprite* bola 
 * @param sf::Vector2f mousePosition
 * @return bool si mouse esta abajo de la bola
 **/
bool Shoe::mouseIsDown(sf::Sprite ball,sf::Vector2f mousePosition){
    return mousePosition.y > ball.getPosition().y+(ball.getTextureRect().height/2);
}

/**
 * @brief funcion cambia la orientacion del zapato
 **/
void Shoe::flip(){
    if(flipped){
        foot.setScale(1,1);
    } else {
        foot.setScale(1,-1);
    }
    flipped = !flipped;
}