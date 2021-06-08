#ifndef BPGUI_H_
#define BPGUI_H_

#include <SFML/Graphics.hpp>
#include "Matrix_BP.h"

class BPGui{
    public:

        sf::Texture players;
        sf::Sprite user; 
        sf::Sprite machine; 
        sf::Texture ballTexture;
        sf::Sprite ball; 
        MatrixBP matrix;
        string matrixString;
        int degreeWhenForce = 0;
        int force = 0;
        int userGoals = 0;
        int machineGoals = 0; 
        bool isTurn = true;
        bool applyingForce = false;
        sf::Vector2i ballPos;
        
        

        BPGui();
        void drawFromMatrix(sf::RenderWindow* window, MatrixBP* matrix);
        void showPathfinderFrom(vector<vector<int>> path, sf::RenderWindow* window);
        void moveFrom(
            MatrixBP backtrackingMatrix,
            sf::RenderWindow* window, 
            sf::Text* userScore, 
            sf::Text* machineScore
        );
        void applyForceBall(
            sf::RenderWindow* window,
            sf::Text* userScore,
            sf::Text* machineScore
        );
        void setUpSprites();
        int random_num();
        static MatrixBP generateMatrixFrom(string matrixString);
        vector<vector<int>> buildPathfinderFrom(string pathfindingString);
        
        
        
};

#endif /* BPGUI_H_ */