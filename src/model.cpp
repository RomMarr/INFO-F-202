#include "model.hpp"
#include "block.hpp"

#include <iostream>
#include <fstream>
#include <FL/Fl.H>

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.


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



Board::Board(const string &level_file) {
    this->create_matrix_from_file(level_file);
}

void Board::reset_level_states() {
    board.clear();
    boxes.clear();
    player = nullptr;
}

void Board::create_matrix_from_file(const string &file_name){
    // Save in memory the current level being played
    current_board_file = file_name;

    // Reset the board matrix
    reset_level_states();

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
                this->board.push_back(block_this_line);
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

shared_ptr<Player> Board::get_player() {
    return player;
}

shared_ptr<Block> Board::get_box_on_pos(tuple<int, int> pos_actual){
    for (auto i: boxes){
        if (i->getPos() == pos_actual) return i;
    }
    return nullptr;
}

vector<shared_ptr<Block>> Board::get_boxes() {
    return boxes;
}

shared_ptr<Player> Board::get_player_on_pos(tuple<int, int> pos_actual){
    if (player->getPos() == pos_actual) {
        return player;
    }
    return nullptr;
}

int Board::get_width() {
    return this->get_height() > 0 ? board.at(0).size() : 0;
}

int Board::get_height() {
    return board.size();
}

int Board::getMaxSteps(){
    return max_steps;
}

bool Board::isInBoard(tuple<int, int> pos){
    if ((get<0>(pos)<0 || get<0>(pos) >= get_width()) || (get<1>(pos) < 0 || get<1>(pos) >= get_height())) {
        // check if it will not leave the board with its movement
        return false;
    } else return true;
}

shared_ptr<Block> Board::get_block(tuple<int, int> coord) {
    return board.at(get<1>(coord)).at(get<0>(coord));
}

void Board::reset_level() {
    create_matrix_from_file(current_board_file);
}

void Board::teleport(tuple<int, int> pos_teleporter){
    int posX =0;
    for (auto line: board){
        int posY = 0;
        for (auto block: line){
            if (block->getType() == Block::BlockType::teleporter){
                 tuple<int,int> pos_block_teleporter = make_tuple(posY,posX);
                 if(pos_block_teleporter != pos_teleporter) {
                    get_player()->setPos(pos_block_teleporter);
                    return;
                 }
             }
            posY++;
        }
        posX++;
    }
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