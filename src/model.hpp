#ifndef _MODEL_H
#define _MODEL_H

#include "stdio.h"

#include <FL/Fl.H>
#include <string>
#include <vector>


using namespace std;

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.


class Block {
public:
    enum BlockType {wall, floor, target, box, light_box, teleporter}; // peut ajouter Block pour extérieur si on veut
private:
    int weight;            // poids du Block
    Fl_Color color;        // couleur du Block 
    const int width = 50;  // largeur du Block
    const int height = 50; // hauteur du Block 
    BlockType type;
    tuple<int,int> pos;
public:
    Block(int weight, Fl_Color color, BlockType type) ;
    void draw(int x, int y);
    void setWeight(int weight);
    void setColor(Fl_Color color);
    void setType(BlockType new_type);
    void setPos(int new_posX, int new_posY);
    tuple<int, int> getPos();
    int getWeight();
    int getWidth();
    int getHeight();
    Fl_Color getColor();
    BlockType getType();
    //~Block();
};


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
    vector<vector<int>> board;
    vector<Block> pos_box;
public:
    Board(const string &level_file);
    void read_file(const string &fileName);
    bool box_on_pos(tuple <int, int>);
};



class Rules{
    shared_ptr<Board> board;
public:
    Rules(shared_ptr<Board> board);
    bool check_move();
    bool check_end();
};

#endif