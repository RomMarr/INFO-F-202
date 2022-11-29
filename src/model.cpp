#include "model.hpp"

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


Block::Block(BlockType type): type{type} {
    if (type == BlockType::box) {
        this->setWeight(6);
    } else if (type == BlockType::light_box) {
        this->setWeight(3);
    }
}

void Block::draw(int x, int y) {
}

void Block::setWeight(int new_weight){
    weight = new_weight; 
}

void Block::setType(BlockType new_type){
    type = new_type;
}

void Block::setPos(tuple<int, int> new_position){
    // get<0>(pos) = new_posX;
    // get<1>(pos)= new_posY;
    pos = new_position;
}

tuple<int, int> Block::getPos(){
    return pos;
}

int Block::getWeight(){
    return weight;
}

int Block::getWidth(){
    return width;
}

int Block::getHeight(){
    return height;
}

Fl_Color Block::getColor(){
    switch (type) {
        case (BlockType::wall): return fl_rgb_color(0, 0, 0); break;
        case (BlockType::box): return fl_rgb_color(255, 128, 0); break;
        case (BlockType::light_box): return fl_rgb_color(255, 128, 0); break;
        case (BlockType::floor): return fl_rgb_color(224, 224, 224);  break;
        case (BlockType::target): return fl_rgb_color(255, 204, 153); break;
        case (BlockType::teleporter): return fl_rgb_color(153, 0, 153); break;
        default: return fl_rgb_color(100, 100, 100); break;
    }
}

Block::BlockType Block::getType(){
    return type;
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
                } else {
                    shared_ptr<Block> box = make_shared<Block>(Block::BlockType::box);
                    (*box).setPos(make_tuple(stoi(line_splitted.at(0)), stoi(line_splitted.at(1))));
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
        if ((*i).getPos() == pos_actual) return i;
    }
    return nullptr;
}

vector<shared_ptr<Block>> Board::get_boxes() {
    return boxes;
}

shared_ptr<Player> Board::get_player_on_pos(tuple<int, int> pos_actual){
    if ((*player).getPos() == pos_actual) {
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

shared_ptr<Block> Board::get_block(tuple<int, int> coord) {
    return board.at(get<1>(coord)).at(get<0>(coord));
}

void Board::reset_level() {
    create_matrix_from_file(current_board_file);
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