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
        this->setColor(fl_rgb_color(255, 128, 0));
        this->setWeight(3);
    } else if (type == BlockType::floor) {
        this->setColor(fl_rgb_color(224, 224, 224));
    } else if (type == BlockType::target) {
        this->setColor(fl_rgb_color(255, 204, 153));
    }
}

void Block::draw(int x, int y) {
}

void Block::setWeight(int new_weight){
    weight = new_weight; 
}

void Block::setColor(Fl_Color new_color){
    color = new_color; 
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
    return color;
}

Block::BlockType Block::getType(){
    return type;
}



Board::Board(const string &level_file) {
    this->create_matrix_from_file(level_file);
}

void Board::create_matrix_from_file(const string &file_name){
    int width = 0, height = 0, line_index = 0;
    bool next_is_player_coord = false;
    string line;
    ifstream file(file_name);

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line_index == 0) {
                vector<string> hw = split(line, " ");
                height = stoi(hw.at(0));
                width = stoi(hw.at(1));
            } else if (line_index <= height) {
                vector<string> this_line = split(line, " ");
                vector<shared_ptr<Block>> block_this_line;
                for (auto block_type_index: this_line) {
                    block_this_line.push_back(make_shared<Block>(grid_int_block_type.at(stoi(block_type_index))));
                }
                this->board.push_back(block_this_line);
            } else {
                if (line == "-") {
                    next_is_player_coord = true;
                } else if (next_is_player_coord) {
                    cout << "player: " << line << endl;
                } else {
                    vector<string> xy = split(line, " ");
                    shared_ptr<Block> box = make_shared<Block>(Block::BlockType::box);
                    (*box).setPos(make_tuple(stoi(xy.at(0)), stoi(xy.at(1))));
                    boxes.push_back(box);
                }
            }

            line_index += 1;
        }
        file.close(); 
    }
}

shared_ptr<Block> Board::get_box_on_pos(tuple<int, int> pos_actual){
    for (auto i: boxes){
        if ((*i).getPos() == pos_actual) return i;
    }
    return nullptr;
}

int Board::get_width() {
    return this->get_height() > 0 ? board.at(0).size() : 0;
}

int Board::get_height() {
    return board.size();
}

shared_ptr<Block> Board::get_block(tuple<int, int> coord) {
    return board.at(get<1>(coord)).at(get<0>(coord));
}


Rules::Rules(shared_ptr<Board> board):board{board}{};

bool Rules::check_move(){

};

bool Rules::check_end(){

}

Player::Player(int posX, int posY): posX{posX}, posY{posY}{};

void Player::setX(int new_X){
    posX = new_X;
}

void Player::setY(int new_Y){
    posY = new_Y;
}

int Player::getX(){
    return posX;
}

int Player::getY(){
    return posY;
}

int Player::getSteps(){
    return steps;
}

