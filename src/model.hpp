#ifndef _MODEL_H
#define _MODEL_H

#include "point.hpp"
#include "block.hpp"
#include "player.hpp"

#include <FL/Fl.H>
#include "stdio.h"
#include <string>
#include <memory>
#include <vector>
#include <tuple>

using namespace std;

class Board{
    static const inline vector<Block::BlockType> grid_int_block_type{Block::BlockType::floor, Block::BlockType::wall, Block::BlockType::target, Block::BlockType::teleporter};
    vector<vector<shared_ptr<Block>>> board; // matrix corresponding to the board
    vector<shared_ptr<Block>> boxes;         // list of all the boxes on the board
    vector<shared_ptr<Block>> teleporters;   // list of all the teleporters in the board
    shared_ptr<Player> player;
    string current_board_file;               // current file path to level's file
    int lvl;                                 // level chosen 
    int max_steps;                           // number maximum of steps a player can do for the chosen level
    int best_steps;                          // best number of steps a player has done for the chosen level
    bool show_board = false;                 // true if the board is ready to be diplayed
    void createMatrixFromFile(const string &file_name); // init all board's states 
    void resetLevelStates();
    int readBestSteps();                    // read bestSteps.txt and returns the best step for the current level
    shared_ptr<Block> readLevel(string block_type_index, int posX, int posY);  // return the block at coord : (posX,posY)
    void readPlayerBoxes(bool next_is_player_coord, vector<string> line_splitted); // init the player and boxes
public:
    shared_ptr<Player> getPlayer();
    shared_ptr<Player> getPlayer(Point position); // nullptr if the player isn't on that position
    shared_ptr<Block> getBlock(Point position);   // ptr to the block of the position given 
    shared_ptr<Block> getBox(Point position);     // nullptr if there is no box on the position
    vector<shared_ptr<Block>> getBoxes();         // list of all boxes' ptr
    vector<shared_ptr<Block>> getTeleporters();   // list of all teleporters' ptr
    bool shouldShowBoard();                       // Should the board be shown (is the board ready)
    void setShowBoard(bool value);
    void setLevel(const string &level_file);      // define the level's number
    void resetLevel();                            // restart the level
    void teleport(Point pos_teleporter);          // teleport the player
    void editBestSteps();                         // edit the best steps file with the new record
    bool checkMove(Point move);                   // check if the move is authorized 
    bool checkMoveTeleport(Point move);           // check if the move to a teleporter is authorized
    bool checkMoveNormal(Point move);             // check if the move to a target or the floor is authorized
    bool checkTeleport(Point pos_teleporter);     // check if the player can teleport 
    bool isBlocked(shared_ptr<Block> box);        // check if the box can still be moved
    bool failureDetection();                      // check if all the boxes can still be moved
    bool isInBoard(Point position);
    bool checkLose();
    bool checkWin();
    int getWidth();
    int getHeight();
    int getMaxSteps();
    int getBestSteps();
    int getLvl();
    int nbBoxOnTarget();
};

#endif