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
    enum BlockType { wall, floor, target, box, light_box, teleporter }; // peut ajouter Block pour extérieur si on veut
private:
    const int width = 50;  // largeur du Block
    const int height = 50; // hauteur du Block 
    BlockType type;
    int weight = -1;       // poids du Block
    tuple<int,int> pos;
public:
    Block(BlockType type) ;
    void draw(int x, int y);
    void setWeight(int weight);
    void setType(BlockType new_type);
    void setPos(tuple<int, int> new_position);
    tuple<int, int> getPos();
    int getWeight();
    int getWidth();
    int getHeight();
    Fl_Color getColor();
    BlockType getType();
    //~Block();
};


class Player{
    tuple<int, int> position;  // position in the matrix
    int steps = 0;
public:
    Player(tuple<int, int> position);
    void setX(int new_X);
    void setY(int new_Y);
    int getX();
    int getY();
    int getSteps();
};


class Board{
    static const inline vector<Block::BlockType> grid_int_block_type{Block::BlockType::floor, Block::BlockType::wall, Block::BlockType::target};
    vector<vector<shared_ptr<Block>>> board;
    vector<shared_ptr<Block>> boxes;
    shared_ptr<Player> player;
    void create_matrix_from_file(const string &file_name);
public:
    Board(const string &level_file);
    shared_ptr<Player> get_player();
    shared_ptr<Block> get_box_on_pos(tuple <int, int>);
    shared_ptr<Player> get_player_on_pos(tuple <int, int>);
    int get_width();
    int get_height();
    shared_ptr<Block> get_block(tuple<int, int> coord);
};



class Rules{
    shared_ptr<Board> board;
public:
    Rules(shared_ptr<Board> board);
    bool check_move();
    bool check_end();
};

#endif