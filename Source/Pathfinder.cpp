#include "Pathfinder.h"

/**
 * @file Pathfinder.cpp
 * @version 1.0
 * @title Pathfinder
 * @brief Manejo de la logica del algoritmo pathfinder A*
 */

/**
 * @brief guarda la mtriz como la matrix del Pathfinder y le da valores iniciales a otras variables
 * @param MatrixBP* puntero a la matriz que se quiere trabajar
 * */
void Pathfinder::setField(MatrixBP* field){
    this->field = field;
    this->currentX = -1; 
    this->currentY = -1;
    openList.erase(openList.begin(),openList.end());
    closedList.erase(closedList.begin(),closedList.end());
}

 MatrixBP Pathfinder::getField(){
     return *this->field;
 }

/**
 * @brief recorre la matriz y a cada nodo le da un valor h con respecto a la posicion de la cancha
 **/
void Pathfinder::setH(){
    int goalX;
    int goalY;
    for(int i = 0; i < this->field->getLength(); i++){
        ListBP* currentList = this->field->at(i);
        int goalAppearance = currentList->check_list("3");
        if(goalAppearance >= 0 ){
            goalX = goalAppearance;
            goalY = i;
        }
    }

    for(int i = 0; i < this->field->getLength(); i++){
        ListBP* currentList = this->field->at(i);
        for(int j = 0; j < currentList->getLength(); j++){
            NodeBPG* currentNode = currentList->at(j);
            int hValue = abs(j-goalX)+abs(i-goalY);
            currentNode->setH(hValue);
        }    
    }
}

/**
 * @brief  Desde la posicion actual, le da valores de G y F a todos los nodos adyacentes y los coloca en la lista abierta
 **/ 
void Pathfinder::checkSurrounding(){ 
    //Se obtiene node del que se esta revisando los adyacentes
    ListBP* lastList = this->field->at(currentY); 
    NodeBPG* lastNode = lastList->at(currentX); 
    //Se empieza a revisar adyacentes
    for(int i = currentY-1; i <= currentY+1;i++){
        //Se revisa si se utiliza valores y validos
        if(i >= 0 && i < this->field->getLength()){
            ListBP* currentList = this->field->at(i);
            for (int j = currentX-1; j <= currentX + 1; j++){
                //Se revisa si se utiliza valores x validos
                if(j >= 0 && j < currentList->getLength()){
                    NodeBPG* currentNode = currentList->at(j);
                    bool is = false;
                    for(NodeBPG* ptr : this->closedList){
                        if(ptr == currentNode){
                            is = true; 
                        }
                    } 
                    if(currentNode->name == "1"){
                        is = true; 
                    }
                    if(is){
                        continue;
                    }

                    //Se asigna valor de G
                    if((i < currentY && j != currentX)||
                    (i > currentY && j != currentX )){
                        int gValue = 14 + lastNode->getG();
                        if(gValue < currentNode->getG() || currentNode->getG() == 0){
                            currentNode->setG(gValue);
                        }
                    } else{
                        int gValue = 10 + lastNode->getG();
                        if(gValue < currentNode->getG() || currentNode->getG() == 0){
                            currentNode->setG(gValue);
                        }
                    }

                    //Se asigna valor de F
                    int fValue = currentNode->getG() + currentNode->getH();
                    if(fValue < currentNode->getF() || currentNode->getF() == 0){
                        currentNode->setF(fValue);
                        currentNode->setParent(lastNode);
                    }

                    //Se añade a openList
                    is = false;
                    for(NodeBPG* ptr : this->openList){
                        if(ptr == currentNode){
                            is = true; 
                        }
                    } 

                    if(!is){
                        openList.push_back(currentNode);
                    }

                }
            }   
        }
    }
}

/**
 * @brief desde la posicion actual, llama a checkSurrounding, cambia la posicion  actual
 * y coloca nodos en la lista cerrada hasta que se encuentra la cancha
 * @return vector<vector<int>> vector con las coordenadas x,y de los nodos del camino encontrado
 **/
vector<vector<int>> Pathfinder::move(){
    
    //Si no existe matriz
    vector<vector<int>> result;
    if(this->field == NULL){
        return result;
    }

    //Si no se tiene posicion inicial
    if(currentY == -1 && currentX == -1){
        for(int i = 0; i < this->field->getLength();i++){
            ListBP* currentList = this->field->at(i);
            int newCurrentX = currentList->check_list("2");
            if(newCurrentX >= 0){
                currentX = newCurrentX;
                currentY = i;
                std::cout << "Ball at: " << newCurrentX << "," << i << std::endl;
            }
        }
    }

    //Se busca la ruta necesaria
    ListBP* currentList = this->field->at(currentY);
    NodeBPG* currentNode = currentList->at(currentX);

    while(currentNode->name != "3"){

        closedList.push_back(currentNode);

        std::cout << "Closed: " << closedList.size() << std::endl;

        checkSurrounding();

        /*
        for(int i = 0; i < this->field->getLength(); i++){
                ListBP* newList = this->field->at(i);
                for(int j = 0; j < newList->getLength(); j++){
                    NodeBPG* newNode = newList->at(j);
                    std::cout << newNode->getG() << "," << newNode->getF() << " ";
                }
                std::cout << std::endl;
            }*/ 

        std::cout << "Open: " << openList.size() << std::endl;

         int nextNodeIndex = 0;

        if(openList.size() > 0){
            int lastF = this->openList.front()->getF();
            for(int i = 0; i < this->openList.size(); i++){
                if(this->openList.at(i)->getF() < lastF){
                    nextNodeIndex = i;
                    lastF = this->openList.at(i)->getF();
                }        
            }

            for(int i = 0; i < this->field->getLength(); i++){
                ListBP* newList = this->field->at(i);
                for(int j = 0; j < newList->getLength(); j++){
                    NodeBPG* newNode = newList->at(j);
                    if(this->openList.at(nextNodeIndex) == newNode){
                        this->currentX = j; 
                        this->currentY = i; 
                        break;
                    }
                }
            } 

            openList.erase(openList.begin()+nextNodeIndex);

            currentList = this->field->at(this->currentY);
            currentNode = currentList->at(this->currentX);    
        }
    }

    while(currentNode->name != "2"){
        vector<int> elements; 
        elements.push_back(currentX);
        elements.push_back(currentY);
        result.push_back(elements);

        bool found = false;
        for(int i = 0; i < this->field->getLength(); i++){
            ListBP* newList = this->field->at(i);
            for(int j = 0; j < newList->getLength(); j++){
                NodeBPG* newNode = newList->at(j);
                if(currentNode->getParent() == newNode){
                    currentX = j;
                    currentY = i;
                    found = true;
                    break; 
                }
                if(found){
                    break;
                }
            }
        } 

        currentList = this->field->at(this->currentY);
        currentNode = currentList->at(this->currentX);  
    }

    

    return result; 
}

