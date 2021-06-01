#ifndef SHOE_H_
#define SHOE_h_

#include <SFML/Graphics.hpp>

class Shoe{
    private:
        sf::Texture shoeTexture;
        sf::Sprite foot; 
        bool flipped = false; 

    public:
        Shoe();
        void rotateShoe(sf::Sprite* ball,sf::Vector2f mousePosition);
        bool mouseIsRight(sf::Sprite ball,sf::Vector2f mousePosition);
        bool mouseIsDown(sf::Sprite ball,sf::Vector2f mousePosition);
        bool getFlipped(){return flipped;};
        void flip();
        sf::Sprite* getFoot(){return &foot;};
};

#endif /*SHOE_H_*/