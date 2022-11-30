#ifndef _MODEL_H
#define _MODEL_H

#include "block.hpp"
// #include "view.hpp"

#include <FL/Fl.H>
#include "stdio.h"
#include <string>
#include <memory>
#include <vector>
#include <tuple>


using namespace std;

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.


class Player{
    tuple<int, int> position;  // position in the matrix
    tuple<int, int> move_asked;
    int steps = 0;
    int weight = 0;
    bool teleported = false;
public:
    Player(tuple<int, int> position);
    void setPos(tuple<int, int> new_pos);
    void setWeight(int new_weight);
    void setMoveAsked(tuple<int, int> new_move_asked);
    void addStep();
    void changeTeleported();
    tuple<int, int> getPos();
    int getSteps();
    int getWeight();
    bool isTeleported();
    tuple<int, int> getMoveAsked();
};


class Board{
    static const inline vector<Block::BlockType> grid_int_block_type{Block::BlockType::floor, Block::BlockType::wall, Block::BlockType::target, Block::BlockType::teleporter};
    vector<vector<shared_ptr<Block>>> board;
    vector<shared_ptr<Block>> boxes;
    shared_ptr<Player> player;
    string current_board_file;
    int lvl;
    int max_steps, best_steps;
    bool show_board = false;
    void create_matrix_from_file(const string &file_name);
    void reset_level_states();
    int read_bestSteps();
public:
    shared_ptr<Player> get_player();
    shared_ptr<Block> get_block(tuple<int, int> coord);
    vector<shared_ptr<Block>> get_boxes();
    shared_ptr<Block> get_box_on_pos(tuple <int, int>);
    shared_ptr<Player> get_player_on_pos(tuple <int, int>);
    void set_show_board(bool value);
    bool should_show_board();
    void set_level(const string &level_file);
    int get_width();
    int get_height();
    int getMaxSteps();
    int get_best_steps();
    int getLvl();
    bool isInBoard(tuple<int, int> pos_block);
    void reset_level();
    void teleport(tuple<int, int> pos_teleporter);
    void write_bestSteps();
};



#endif