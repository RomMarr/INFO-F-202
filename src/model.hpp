#ifndef _MODEL_H
#define _MODEL_H

#include "stdio.h"

#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>
#include <tuple>


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
    int weight;       // poids du Block
    tuple<int,int> pos;    // position du Block
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
    int weight = 0;
    tuple<int, int> move_asked;
public:
    Player(tuple<int, int> position);
    void setPos(tuple<int, int> new_pos);
    void setWeight(int new_weight);
    void setMoveAsked(tuple<int, int> new_move_asked);
    void addStep();
    tuple<int, int> getPos();
    int getSteps();
    int getWeight();
    tuple<int, int> getMoveAsked();
};


class Board{
    static const inline vector<Block::BlockType> grid_int_block_type{Block::BlockType::floor, Block::BlockType::wall, Block::BlockType::target};
    vector<vector<shared_ptr<Block>>> board;
    vector<shared_ptr<Block>> boxes;
    shared_ptr<Player> player;
    void create_matrix_from_file(const string &file_name);
    int max_steps;
public:
    Board(const string &level_file);
    shared_ptr<Player> get_player();
    shared_ptr<Block> get_box_on_pos(tuple <int, int>);
    shared_ptr<Player> get_player_on_pos(tuple <int, int>);
    int get_width();
    int get_height();
    int getMaxSteps();
    shared_ptr<Block> get_block(tuple<int, int> coord);
};



#endif