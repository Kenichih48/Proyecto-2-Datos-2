#pragma once
#ifndef GENETICPUZZLE_GENETICALGORITHM_H
#define GENETICPUZZLE_GENETICALGORITHM_H
#include "UtilityProgram.h"
#include "Piece.h"
#include "xmlParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class GeneticAlgorithm{
public:
    GeneticAlgorithm(string image, int numPieces, bool primo){
        matrix = utility(numPieces, matrix);
        loadPosFitness(matrix);
        loadImages(image, matrix->getRows(), matrix->getCols());
        windowGeneticPuzzle(matrix, numPieces, primo);
    }
    vector <vector<int>> puzzleMap;
    vector <int> tempMap;
    MatrixGP<int> *matrix;

    Texture puzzleTexture;
    Texture playTexture, rewindTexture, skipTexture;

    bool playing = false;

    RectangleShape playButton, rewindButton, skipButton, buttonsBackground;

    ListGP<Vector2f>* listPosImages = new ListGP<sf::Vector2f>();
    ListGP<Vector2f>* listPosFitness = new ListGP<sf::Vector2f>();
    ListGP<MatrixNodeBP<int>*>* listFitness = new ListGP<MatrixNodeBP<int>*>();
    ListGP<int>* listMutations = new ListGP<int>();
    ListGP<MatrixGP<int>*>* listGenerations = new ListGP<MatrixGP<int>*>();

    XmlParser xmlParser;

    float dimensionX;
    float dimensionY;


/// Function that loads the images
/// \param image
/// \param numPieces
/// \param rows
/// \param cols
    void loadImages(const string& image, int rows, int cols)
    {
        //Load the texture of the image
        puzzleTexture.loadFromFile(image);
        cout << "Starting to load new textures" << endl;
        playTexture.loadFromFile("PlayButton.png");
        rewindTexture.loadFromFile("RewindButton.png");
        skipTexture.loadFromFile("SkipButton.png");
        cout << "Loaded all textures succesfully" << endl;

        //Get its dimensions
        dimensionX = puzzleTexture.getSize().x;
        dimensionY = puzzleTexture.getSize().y;

        float col = dimensionX / cols;
        float row = dimensionY / rows;

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                listPosImages->addData(sf::Vector2f(i*row,j*col));
            }
        }
    }
/// Function that load the position fitness of the images
/// \param matrix
    void loadPosFitness(MatrixGP<int>* matrix)
    {
        for(int i = 0; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                listPosFitness->addData(sf::Vector2f(i,j));
            }
        }
    }

/// Function that sorts the list of fitness
/// \param list
    void sortFitness(ListGP<MatrixNodeBP<int>*>* list)
    {
        MatrixNodeBP<int> *tempData;
        NodeBP<MatrixNodeBP<int>*> *auxNode = list->getHead();
        NodeBP<MatrixNodeBP<int>*> *temp = auxNode;

        while(auxNode)
        {
            temp = auxNode;
            while(temp->next)
            {
                temp = temp->next;

                if(auxNode->data->getH() < temp->data->getH())
                {
                    tempData = auxNode->data;
                    auxNode->data = temp->data;
                    temp->data = tempData;
                }
            }
            auxNode = auxNode->next;
        }
    }

/// Function that calculates the fitness of each individual
/// \param matrix
    void loadFitness(MatrixGP<int>* matrix)
    {
        int position;
        int xEnd;
        int yEnd;

        for(int i = 0 ; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                MatrixNodeBP<int>* node = matrix->getNodePos(i, j);
                position = node->getData();
                xEnd = listPosFitness->getDataPos(position).x;
                yEnd = listPosFitness->getDataPos(position).y;
                node->setH(abs(xEnd - i) + abs(yEnd - j));
                listFitness->addData(node);
            }
        }
        sortFitness(listFitness);
    }

/// Function that changes the position of the selected individuals
/// \param matrix
/// \param list
/// \return
    MatrixGP<int>* crossover(MatrixGP<int>* matrix, ListGP<MatrixNodeBP<int>*>* list)
    {
        int position1 = matrix->getNodeData(matrix,list->getDataPos(0)->getData())->getData();
        int position2 = matrix->getNodeData(matrix,list->getDataPos(1)->getData())->getData();
        int position3 = matrix->getNodeData(matrix,list->getDataPos(2)->getData())->getData();

        matrix->getNodeData(matrix,list->getDataPos(0)->getData())->setData(position3);
        matrix->getNodeData(matrix,list->getDataPos(1)->getData())->setData(position1);
        matrix->getNodeData(matrix,list->getDataPos(2)->getData())->setData(position2);

        return matrix;
    }

/// Function that mutates an individual
/// \param numPieces
/// \param matrix
    void mutation(int numPieces, MatrixGP<int>* matrix)
    {
        int mutation;
        srand(time(NULL));
        mutation = (rand() % 100);

        if(mutation <= 30)
        {
            //Mutate
            int number1;
            int number2;
            bool done = false;

            while(!done)
            {
                srand(time(NULL));
                number1 =(rand() % numPieces);
                srand(time(NULL));
                number2 =(rand() % numPieces);
                if(number1 != number2) {
                    done = true;
                }
            }

            listMutations->addData(number1);

            int position1 = matrix->getNodeData(matrix, number1)->getData();
            int position2 = matrix->getNodeData(matrix, number2)->getData();

            matrix->getNodeData(matrix, number1)->setData(position2);
            matrix->getNodeData(matrix, number2)->setData(position1);
        }
    }

/// Function that loads the image puzzle map
/// \param matrix
    void loadPuzzle(MatrixGP<int>* matrix)
    {
        //Clear the previous tempMap and map
        tempMap.clear();
        puzzleMap.clear();

        //Travel the matrix
        for(int i = 0; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                MatrixNodeBP<int>* node = matrix->getNodePos(i, j);
                tempMap.push_back(node->getData());
            }
            puzzleMap.push_back(tempMap);
            tempMap.clear();
        }
    }

/// Function that loads the interface of the genetic puzzle
/// \param matrix
/// \param numPieces
/// \param primo
    void windowGeneticPuzzle(MatrixGP<int>* matrix, int numPieces, bool primo)
    {
        //Create the window
        RenderWindow window(sf::VideoMode(dimensionX,dimensionY+150,32), "Genetic Puzzle");
        window.setVerticalSyncEnabled(true);
        Clock clock;
        Font font;
        font.loadFromFile("Ubuntu-M.ttf");

        //Adds the matrix generation to the list of generations
        MatrixGP<int>* newMatrix = new MatrixGP<int>(matrix->getRows(), matrix->getCols());
        for (int i = 0; i < newMatrix->getRows(); i++){
            for (int j = 0; j < newMatrix->getCols(); j++) {
                newMatrix->setNode(i, j, matrix->getNodePos(i, j)->getData());
            }
        }
        listGenerations->addGeneration(newMatrix);

        int limitGenerations = numPieces * 75;
        int same;

        //Calculates the function fitness of the actual generation
        int generation = 0;
        int generation_ = 0;
        bool doingGens = false;

        loadFitness(listGenerations->getDataPos(generation));

        while (!doingGens)
        {
            //Crossover
            matrix = crossover(matrix,listFitness);
            MatrixGP<int>* newMatrix2 = new MatrixGP<int>(matrix->getRows(), matrix->getCols());
            for (int i = 0; i < newMatrix2->getRows(); i++){
                for (int j = 0; j < newMatrix2->getCols(); j++) {
                    newMatrix2->setNode(i, j, matrix->getNodePos(i, j)->getData());
                }
            }

            //Mutation
            if(listMutations->getSize() != 0) {
                listMutations->delAll();
                listMutations = new ListGP<int>();
            }
            mutation(numPieces,matrix);

            //Adds new generation
            listGenerations->addGeneration(newMatrix2);
            generation_++;

            //Calculates the function fitness of the new generation
            listFitness->delAll();
            listFitness = new ListGP<MatrixNodeBP<int>*>();
            loadFitness(listGenerations->getDataPos(generation_));

            //Close the window if it gets to the solution or the limit of generation is achieved
            same = 0;
            for(int x = 0; x < listFitness->getSize(); x++)
            {
                if(listFitness->getDataPos(x)->getH() == 0)
                    same++;
            }

            if(same == numPieces)
            {
                doingGens = true;
            }

            if(listGenerations->getSize() == limitGenerations )
            {
                doingGens = true;
            }
        }

        for (int i = 0; i < listGenerations->getSize(); i++)
        {
            int rows = listGenerations->getDataPos(i)->getRows();
            int cols = listGenerations->getDataPos(i)->getCols();
            int piece = 1;
            xmlParser.buildGenerationXml(i, rows, cols);
            for (int j = 0; j < listGenerations->getDataPos(i)->getRows(); j++)
            {
                for (int k = 0; k < listGenerations->getDataPos(i)->getCols(); k++)
                {
                    xmlParser.buildPieceXml(piece, j, k, listGenerations->getDataPos(i)->getNodePos(j, k)->getData());
                    piece++;
                }
            }
            xmlParser.saveXml(i);
        }
        loadPuzzle(listGenerations->getDataPos(generation));


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        if (playButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && !playing)
                            playing = true;
                        else if (playButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && playing)
                            playing = false;
                        else if (rewindButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && generation >= 1) {
                            generation--;
                            loadPuzzle(listGenerations->getDataPos(generation));
                            playing = false;
                        }
                        else if (skipButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && generation <= 9){
                            generation++;
                            loadPuzzle(listGenerations->getDataPos(generation));
                            playing = false;
                        }
                    }
                }
                switch(event.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                            window.close();
                }
                Time timer = clock.getElapsedTime();

                if (generation != generation_ && playing && timer >= seconds(2))
                {
                    //Advance one generation
                    generation++;
                    //Load the Map
                    loadPuzzle(listGenerations->getDataPos(generation));
                    //Pause the reproduction for 2 seconds
                    clock.restart();
                }

                //Draw the Puzzle Map
                window.clear(sf::Color::Black);

                float row = dimensionX / matrix->getCols();
                float col = dimensionY / matrix->getRows();

                for (int i = 0; i < puzzleMap.size(); i++) {
                    for (int j = 0; j < puzzleMap[i].size(); j++) {
                        sf::Vector2f positionMap = sf::Vector2f(j * row, i * col);
                        sf::Vector2f rect = sf::Vector2f(row, col);
                        sf::Vector2f positionRect = listPosImages->getDataPos(puzzleMap[i][j]);
                        Piece *p = new Piece(positionMap, puzzleTexture, rect, positionRect);
                        window.draw(p->piece);
                    }
                }

                buttonsBackground.setFillColor(Color(60,60,60,255));
                buttonsBackground.setSize(Vector2f(dimensionX, 150));
                buttonsBackground.setPosition(0,dimensionY);
                playButton.setTexture(&playTexture);
                playButton.setSize(Vector2f(120,120));
                playButton.setPosition((dimensionX/2)-(playButton.getSize().x/2),dimensionY+25);
                rewindButton.setTexture(&rewindTexture);
                rewindButton.setSize(Vector2f(120,120));
                rewindButton.setPosition((dimensionX/4)-(playButton.getSize().x/2),dimensionY+25);
                skipButton.setTexture(&skipTexture);
                skipButton.setSize(Vector2f(120,120));
                skipButton.setPosition((3*dimensionX/4)-(playButton.getSize().x/2),dimensionY+25);

                window.draw(buttonsBackground);
                window.draw(playButton);
                window.draw(rewindButton);
                window.draw(skipButton);

                //Draw the generation text
                Text textGeneration;
                textGeneration.setFont(font);
                string textG = to_string(generation);
                textGeneration.setString("Generation: " + textG + " of " + to_string(generation_) + " generations.");
                textGeneration.setCharacterSize(20);
                textGeneration.setPosition(5, dimensionY+5);
                window.draw(textGeneration);

                window.display();
            }
        }
    }
    ListGP<MatrixGP<int>*>* getListGenerations()
    {
        return listGenerations;
    }
};

#endif //GENETICPUZZLE_GENETICALGORITHM_H
