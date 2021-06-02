#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "Matrix_BP.h"
#include <vector>

class Pathfinder{ 
    private: 
        MatrixBP* field = NULL; 
        vector<NodeBPG*> openList;
        vector<NodeBPG*> closedList;
        int currentY;
        int currentX;
    public: 
        Pathfinder(){
            this->currentX = -1; 
            this->currentY = -1;
        }
        void checkSurrounding();
        void setH();
        void setField(MatrixBP* field);
        MatrixBP getField();
        vector<vector<int>> move();
};



#endif /* PATHFINDER_H_ */