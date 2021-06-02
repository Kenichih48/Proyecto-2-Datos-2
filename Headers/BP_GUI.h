#ifndef BPGUI_H_
#define BPGUI_H_

#include <SFML/Graphics.hpp>
#include "Matrix_BP.h"

class BPGui{
    public:

        sf::Texture players;
        sf::Sprite user; 
        sf::Sprite machine; 

        BPGui();
        void drawFromMatrix(sf::RenderWindow* window, MatrixBP* matrix);
        void setUpSprites();
        MatrixBP generateMatrixFrom(string matrixString);
        
};

#endif /* BPGUI_H_ */