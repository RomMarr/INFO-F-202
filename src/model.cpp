#include "model.hpp"
#include "block.hpp"

#include <iostream>
#include <fstream>
#include <FL/Fl.H>

// The following function come from https://stackoverflow.com/a/46931770/7905936
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void Board::resetLevelStates() {
    board.clear();
    boxes.clear();
    player = nullptr;
}

void Board::createMatrixFromFile(const string &file_name){
    // Save in memory the current level being played
    current_board_file = file_name;

    // Reset the board matrix
    resetLevelStates();

    readBestSteps();

    int width = 0, height = 0, line_index = 0;
    bool next_is_player_coord = false;
    string line;
    ifstream file(file_name);

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> line_splitted = split(line, " ");
            if (line_index == 0) {
                height = stoi(line_splitted.at(0));
                width = stoi(line_splitted.at(1));
            } else if (line_index <= height) {
                vector<shared_ptr<Block>> block_this_line;
                for (auto block_type_index: line_splitted) {
                    block_this_line.push_back(make_shared<Block>(grid_int_block_type.at(stoi(block_type_index))));
                }
                board.push_back(block_this_line);
            } else {
                if (line == "-") {
                    next_is_player_coord = true;
                } else if (next_is_player_coord) {
                    player = make_shared<Player>(make_tuple(stoi(line_splitted.at(0)), stoi(line_splitted.at(1))));
                    max_steps = stoi(line_splitted.at(2));
                } else {
                    shared_ptr<Block> box = make_shared<Block>((stoi(line_splitted.at(2)) ? Block::BlockType::light_box : Block::BlockType::box));
                    box->setPos(make_tuple(stoi(line_splitted.at(0)), stoi(line_splitted.at(1))));
                    boxes.push_back(box);
                }
            }

            line_index += 1;
        }
        file.close(); 
    }
}

void Board::setShowBoard(bool value) {
    show_board = value;
}

bool Board::shouldShowBoard() {
    return show_board;
}

void Board::setLevel(const string &level_file) {
    if (level_file.size()== 12) { // if level between 0 and 9 
        lvl = static_cast<int>(level_file[7]) -48;
    }  else { // if level between 10 and 99
        lvl = (static_cast<int>(level_file[7])-48)*10 + static_cast<int>(level_file[8])-48;
    }
    createMatrixFromFile(level_file);
    setShowBoard(true);
}

shared_ptr<Player> Board::getPlayer() {
    return player; // shared ptr to the player
}

shared_ptr<Block> Board::getBox(tuple<int, int> pos_actual){
    for (auto box: boxes){  // go through all the boxes
        if (box->getPos() == pos_actual) return box;  // shared ptr to the box
    }
    return nullptr;
}

vector<shared_ptr<Block>> Board::getBoxes() {
    return boxes;  // vector of all the boxes of the board
}

shared_ptr<Player> Board::getPlayer(tuple<int, int> pos_actual){
    if (player->getPos() == pos_actual) { // if the player is on the position given
        return player;  // shared ptr to the player 
    }
    return nullptr;
}

int Board::getWidth() {
    return getHeight() > 0 ? board.at(0).size() : 0;
}

int Board::getHeight() {
    return board.size();
}

int Board::getMaxSteps(){
    return max_steps;
}

int Board::getLvl() {
    return lvl;
}

bool Board::isInBoard(tuple<int, int> pos){
    if ((get<0>(pos)<0 || get<0>(pos) >= getWidth()) || (get<1>(pos) < 0 || get<1>(pos) >= getHeight())) {
        // check if it will leave the board with its movement
        return false;
    } else return true;
}

shared_ptr<Block> Board::getBlock(tuple<int, int> coord) {
    return board.at(get<1>(coord)).at(get<0>(coord));  // shared ptr to the block at the position given
}

void Board::resetLevel() {
    createMatrixFromFile(current_board_file);
}

void Board::teleport(tuple<int, int> pos_teleporter){
    int posY =0;
    for (auto line: board){  // go through the board
        int posX = 0;
        for (auto block: line){ // go through the board
            if (block->getType() == Block::BlockType::teleporter){  // if block is a teleporter
                 tuple<int,int> pos_block_teleporter = make_tuple(posX,posY);  
                 if(pos_block_teleporter != pos_teleporter) {  // if the teleporter is not the one the player is using
                    getPlayer()->setPos(pos_block_teleporter); // teleport (change position) the player
                    return;  // leave the loop
                 }
             }
            posX++;
        }
        posY++;
    }
}

int Board::getBestSteps() {
    return best_steps;
}

int Board::readBestSteps(){
    int index_line = 0;
    int bestSteps = 9999;
    string line;
    ifstream file("bestSteps.txt");
    if (file.is_open()) {  // open the bestSteps file
        while (getline(file, line)) {  // go through all the lines
            if (index_line == getLvl()) bestSteps = stoi(line);  // get the best score of the level
            index_line++;
        }
        file.close();  // close the file
    } 
    best_steps = bestSteps;
}

void Board::writeBestSteps(){
    int index_line = 0; // matches the levels (lvl = 0 -> index_line = 0 )
    string line;
    ofstream file_write("tmp.txt");
    if (file_write.is_open()) {  // open the temporary file
        ifstream file_read("bestSteps.txt");
        if (file_read.is_open()) { // open the bestSteps file 
            while (getline(file_read, line)) {  // go through all the lines of the bestSteps file
                if (index_line == getLvl()) file_write << player->getSteps() << endl;  // change the line where the best record has been brocken
                else file_write << line << endl;  // copy each line in the temporary file
                index_line++;
            } file_read.close();  // close the bestSteps file
        } else cerr << "Impossible␣d’ouvrir␣le␣fichier␣" << "bestSteps.txt" << endl;  // if bestSteps file can not be opened
        file_write.close();  //  close  the temporary file 
        remove("bestSteps.txt"); // delete the bestSteps file 
        rename("tmp.txt", "bestSteps.txt");  // rename de temporary file to the bestSteps file
    } else cerr << "Impossible␣d’ouvrir␣le␣fichier␣" << "tmp.txt" << endl; // if temporary file can not be opened
}

int Board::nbBoxOnTarget() {
    int nb_box = 0;
    for (shared_ptr<Block> box: getBoxes()) {  // go through all the boxes 
        if (getBlock(box->getPos())->getType() == Block::BlockType::target) {  // true if the box is on a target
            nb_box += 1;
        }
     } return nb_box;
}

Player::Player(tuple<int, int> position): position{position} {};

void Player::setPos(tuple<int, int> new_pos){
    position = new_pos;
}

void Player::setWeight(int new_weight){
    weight = new_weight;
}

void Player::setMoveAsked(tuple<int, int> new_move_asked){
    move_asked = new_move_asked;
}

void Player::addStep(){
    steps += 1;
}

void Player::changeTeleported(){
    teleported = (!teleported);
}

tuple<int, int> Player::getPos(){
    return position;
}

tuple<int, int> Player::getMoveAsked(){
    return move_asked;
}

int Player::getSteps(){
    return steps;
}

int Player::getWeight(){
    return weight;
}

bool Player::isTeleported(){
    return teleported;
}