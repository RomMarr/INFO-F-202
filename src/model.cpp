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

    read_bestSteps();

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

void Board::set_show_board(bool value) {
    show_board = value;
}

bool Board::should_show_board() {
    return show_board;
}

void Board::set_level(const string &level_file) {
    if (level_file.size()== 12) { // if level between 0 and 9 
        lvl = static_cast<int>(level_file[7]) -48;
    }  else { // if level between 10 and 99
        lvl = (static_cast<int>(level_file[7])-48)*10 + static_cast<int>(level_file[8])-48;
    }
    
    create_matrix_from_file(level_file);
    set_show_board(true);
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
    return get_height() > 0 ? board.at(0).size() : 0;
}

int Board::get_height() {
    return board.size();
}

int Board::getMaxSteps(){
    return max_steps;
}

int Board::getLvl() {
    return lvl;
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

int Board::get_best_steps() {
    return best_steps;
}

int Board::read_bestSteps(){
    int index_line = 0;
    int bestSteps = 9999;
    string line;
    ifstream file("bestSteps.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (index_line == getLvl()) bestSteps = stoi(line);
            index_line++;
        }
    file.close();
    }

    best_steps = bestSteps;
}

void Board::write_bestSteps(){
    int index_line = 0;
    string line;
    ofstream file_write("tmp.txt");
    if (file_write.is_open()) {  // ouvre le fichier d'écriture du message décodé
        ifstream file_read("bestSteps.txt");
        if (file_read.is_open()) {
            while (getline(file_read, line)) {
                if (index_line == getLvl()) file_write << player->getSteps() << endl;  // écrit le message codé dans le fichier txt;
                else file_write << line << endl;  // écrit le message codé dans le fichier txt
                index_line++;
            } file_read.close();
        } else cerr << "Impossible␣d’ouvrir␣le␣fichier␣" << "bestSteps.txt" << endl;
        file_write.close();  //  ferme le fichier txt contenant le message codé
        remove("bestSteps.txt");
        rename("tmp.txt", "bestSteps.txt");
    } else cerr << "Impossible␣d’ouvrir␣le␣fichier␣" << "tmp.txt" << endl;
}

int Board::nb_box_on_target() {
    int i = 0;
    
    for (shared_ptr<Block> box: get_boxes()) {
        if (get_block(box->getPos())->getType() == Block::BlockType::target) {
            i += 1;
        }
     }

     return i;
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