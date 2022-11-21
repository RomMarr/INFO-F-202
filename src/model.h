#ifndef _MODEL_H
#define _MODEL_H

#include "stdio.h"
#include <string>
#include <vector>
using namespace std;
// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.




class Player{
    int posX, posY;  // position in the matrix
    int steps = 0;
public:
    Player(int posX, int posY);
    void setX(int new_X);
    void setY(int new_Y);
    int getX();
    int getY();
    int getSteps();
};

class Board{
    vector<vector<int>> matrix;
public:
    void file_to_matrix(string fileName);
};



class Rules{
    shared_ptr<Board> board;
public:
    Rules(shared_ptr<Board> board);
    bool check_move();
    bool check_end();
};

#endif