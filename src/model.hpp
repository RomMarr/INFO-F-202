#ifndef _MODEL_H
#define _MODEL_H

#include "point.hpp"
#include "block.hpp"
#include "player.hpp"
// #include "view.hpp"

#include <FL/Fl.H>
#include "stdio.h"
#include <string>
#include <memory>
#include <vector>
#include <tuple>

using namespace std;

class Board{
    static const inline vector<Block::BlockType> grid_int_block_type{Block::BlockType::floor, Block::BlockType::wall, Block::BlockType::target, Block::BlockType::teleporter};
    vector<vector<shared_ptr<Block>>> board;
    vector<shared_ptr<Block>> boxes;
    vector<shared_ptr<Block>> teleporters;
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
    shared_ptr<Player> getPlayer(Point position); // get a ptr to the player on position or nullptr if the player isn't on that position
    shared_ptr<Block> getBlock(Point position);   // get a ptr to the block of the position given 
    shared_ptr<Block> getBox(Point position);     // get a ptr to the box on the position or nullptr if there is no box on it
    vector<shared_ptr<Block>> getBoxes();         // get a list of ptr of all the boxes
    vector<shared_ptr<Block>> getTeleporters();   // get a list of ptr of all the teleporters
    shared_ptr<Block> readLevel(string block_type_index, int posX, int posY);  // read level.txt and return the block of the board at coord : (posX,posY)
    void setShowBoard(bool value);
    bool shouldShowBoard();         // Should the board be shown (is the board ready)
    void setLevel(const string &level_file);
    void readPlayerBoxes(bool next_is_player_coord, vector<string> line_splitted); // read lvl.txt and init player and boxes
    int getWidth();
    int getHeight();
    int getMaxSteps();
    int getBestSteps();
    int getLvl();
    bool isInBoard(Point position);
    void resetLevel();
    void teleport(Point pos_teleporter);
    void writeBestSteps(); // Edit the best steps file with the new record
    int nbBoxOnTarget();
};

#endif