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

class Player{
    tuple<int, int> position;    // position in the matrix
    tuple<int, int> move_asked;  // tuple to add to the position of the player 
    int steps = 0;               // number of steps the player has done
    int weight = 0;              // weight of the boxes the player is pushing
    bool teleported = false;     // true if the player use a teleporter
public:
    Player(tuple<int, int> position);
    void setPos(tuple<int, int> new_pos);  
    void setWeight(int new_weight);
    void setMoveAsked(tuple<int, int> new_move_asked);
    void addStep();                // add a step to steps
    void changeTeleported();       // change de boolean of teleprted
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
    int lvl;         // level chosen 
    int max_steps;   // number max of steps a player can do for the level chosen
    int best_steps;  // best number of steps a player has done for the level chosen
    bool show_board = false;
    void createMatrixFromFile(const string &file_name);
    void resetLevelStates(); // Remove all informations in board
    int readBestSteps();
public:
    shared_ptr<Player> getPlayer(); // Get the player
    shared_ptr<Player> getPlayer(tuple <int, int> position); // Get the player on position
    shared_ptr<Block> getBlock(tuple<int, int> position);
    vector<shared_ptr<Block>> getBoxes();
    shared_ptr<Block> getBox(tuple <int, int>);
    void setShowBoard(bool value);
    bool shouldShowBoard(); // Should the board be shown (is the board ready)
    void setLevel(const string &level_file);
    int getWidth();
    int getHeight();
    int getMaxSteps();
    int getBestSteps();
    int getLvl();
    bool isInBoard(tuple<int, int> position);
    void resetLevel();
    void teleport(tuple<int, int> pos_teleporter);
    void writeBestSteps(); // Edit the best steps file with the new record
    int nbBoxOnTarget();
};



#endif