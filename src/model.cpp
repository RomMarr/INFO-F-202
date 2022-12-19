#include "model.hpp"

#include "block.hpp"
#include "player.hpp"
#include "point.hpp"
#include "controller.hpp"
#include "constants.hpp"

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
    teleporters.clear();
    player = nullptr;
}

shared_ptr<Block> Board::readLevel(string block_type_index, int posX, int posY){
    if (stoi(block_type_index)> 3) {
        shared_ptr block_here = make_shared<Block>(Block::BlockType::target);
        block_here->setIdColor(1);
        block_here->setPos(Point{posX, posY});
        return block_here;
    } else {
        shared_ptr block_here = make_shared<Block>(grid_int_block_type.at(stoi(block_type_index)));
        block_here->setPos(Point{posX, posY});
        Block::BlockType block_type = block_here->getType();
        if (block_type == Block::BlockType::teleporter) teleporters.push_back(block_here);
        return block_here;
    }
}

void Board::readPlayerBoxes(bool next_is_player_coord, vector<string>line_splitted){
    if (next_is_player_coord) {
        player = make_shared<Player>(Point(stoi(line_splitted.at(0)), stoi(line_splitted.at(1))));
        max_steps = stoi(line_splitted.at(2));
    } else {
        shared_ptr<Block> box = make_shared<Block>((stoi(line_splitted.at(2)) ? Block::BlockType::light_box : Block::BlockType::heavy_box));
        box->setPos(Point{stoi(line_splitted.at(0)), stoi(line_splitted.at(1))});
        Block::BlockType box_type = box->getType();
        if (box_type == Block::BlockType::heavy_box){
            if (line_splitted.size()>= 4) box->setIdColor(1);
        }boxes.push_back(box);
    }
}

void Board::createMatrixFromFile(const string &file_name){
    // Save in memory the current level being played
    current_board_file = file_name;

    // Reset the board matrix
    resetLevelStates();

    readBestSteps();
    int height = 0, line_index = 0;
    bool next_is_player_coord = false;
    string line;
    ifstream file(file_name);
    if (file.is_open()) {
        int posX = 0, posY = 0;
        while (getline(file, line)) {
            vector<string> line_splitted = split(line, " ");
            if (line_index == 0) height = stoi(line_splitted.at(0));
            else if (line_index <= height) {
                vector<shared_ptr<Block>> block_this_line;
                for (auto block_type_index: line_splitted) {
                    block_this_line.push_back(readLevel(block_type_index, posX, posY));
                    posX++;
                } posX = 0;
                posY ++;
                board.push_back(block_this_line);
            } else {
                if (line == "-") next_is_player_coord = true;
                else readPlayerBoxes(next_is_player_coord, line_splitted);
            } line_index += 1;
        } file.close(); 
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

shared_ptr<Player> Board::getPlayer(Point pos_actual){
    if (player->getPos() == pos_actual) { // if the player is on the position given
        return player;  // shared ptr to the player 
    }
    return nullptr;
}

shared_ptr<Block> Board::getBox(Point actual_pos){
    for (auto box: boxes){  // go through all the boxes
        if (box->getPos() == actual_pos) return box;  // shared ptr to the box
    }
    return nullptr;
}

vector<shared_ptr<Block>> Board::getBoxes() {
    return boxes;  // vector of all the boxes of the board
}

vector<shared_ptr<Block>> Board::getTeleporters() {
    return teleporters;  // vector of all the teleporters of the board
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

bool Board::isInBoard(Point pos){
    if (pos.getPosX() < 0 || pos.getPosX() >= getWidth() || pos.getPosY() < 0 ||pos.getPosY() >= getHeight()) {
        // check if it will leave the board with its movement
        return false;
    } else return true;
}

shared_ptr<Block> Board::getBlock(Point coord) {
    return board.at(coord.getPosY()).at(coord.getPosX());  // shared ptr to the block at the position given
}

void Board::resetLevel() {
    createMatrixFromFile(current_board_file);
}

void Board::teleport(Point pos_teleporter){
    vector<shared_ptr<Block>> teleporters = getTeleporters();
    for (auto teleporter: teleporters){  // go through the teleporters
        if(teleporter->getPos() != pos_teleporter) {  // if the teleporter is not the one the player is using
            if (! getBox(teleporter->getPos())) player->setPos(teleporter->getPos()); // if no box on the other teleporter
                return; 
        }
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
        shared_ptr<Block> block_of_box = getBlock(box->getPos());
        if (block_of_box->getType() == Block::BlockType::target && box->getIdColor() == block_of_box->getIdColor()) {  // true if the box is on a target
            nb_box += 1;
        }
     } return nb_box;
}


bool Board::checkWin(){
    if (nbBoxOnTarget() != static_cast<int>(getBoxes().size())) return false; // if not all boxes are on a target
    if (getBestSteps() == -1 || getBestSteps() > player->getSteps()) writeBestSteps(); // if best steps has been beaten
    return true;
}

bool Board::checkLose(){
    return (player->getSteps() >= getMaxSteps() || failureDetection()); // true if game over
}


bool Board::checkMove(Point move){
    Point new_pos = player->getPos() + move; // new possible position of the player (not checked yet)

    if (!isInBoard(new_pos)) return false; 
    // check if the player will not leave the board with its movement
    if (player->getWeight()> MAX_PLAYER_WEIGHT) return false;
    // A player can push max a weight lesser than 10
    
    Block::BlockType destination_type = getBlock(new_pos)->getType();  
    // type of the block of the possible new position
    
    if (destination_type == Block::BlockType::wall) return false;
    // if the block of arrival is a wall
    else if (destination_type == Block::BlockType::floor || destination_type == Block::BlockType::target){
    // if the block of arrival is a floor or a target
        return checkMoveNormal(move);
    } else if (destination_type == Block::BlockType::teleporter){
    // if the block of arrival is a teleporter
        return checkMoveTeleport(move);
    }else return false;
}


bool Board::checkMoveTeleport(Point move){
    Point pos_player = player->getPos();
    Point new_pos = pos_player + move; // new possible position of the player or box (not checked yet)
    Point move_asked = player->getMoveAsked();  // movement add to the player's position to get his new position
    Point new_pos_box = new_pos + move_asked; // new possible position of the box (not checked yet)
    shared_ptr<Block> box_on_move = getBox(new_pos);  // ptr to the box if there is one, nullptr if not
    if (box_on_move){ // if box on the new_pos of the player
            player->setWeight(player->getWeight()+ box_on_move->getWeight()); // add the weight of the box
            if (checkMove(move + move_asked)){  // if move authorized
                if (getBlock(pos_player+ move_asked)->getType()==Block::BlockType::teleporter){
                    // type of the block of the new_pos is a teleporter
                    getBox(new_pos)->setPos(new_pos_box); // change de position of the box
                    if (checkTeleport(new_pos)) { // if player can teleport
                        player->changeTeleported(); // teleported = true
                        return true;
                    }return false;
                }getBox(new_pos)->setPos(new_pos_box); // change de position of the box
            } 
    }if (getBlock(pos_player+ move_asked)->getType()==Block::BlockType::teleporter){
    // type of the block of the new_pos is a teleporter
        if (checkTeleport(new_pos)) { // if player can teleport
            player->changeTeleported(); // teleported = true
            return true;
        }return false;
    }return true;
}

bool Board::checkMoveNormal(Point move){
    Point pos_player = player->getPos(); 
    Point new_pos = pos_player + move; // new possible position of the player (not checked yet)
    Point move_asked = player->getMoveAsked();  // movement add to the player's position to get his new position
    Point new_pos_box = new_pos + move_asked; // new possible position of the box (not checked yet)
    shared_ptr<Block> box_on_move = getBox(new_pos);  // ptr to the box if there is one, nullptr if not
    if (box_on_move){  // check if ptr != nullptr
            player->setWeight(player->getWeight()+ box_on_move->getWeight()); // add the weight of the box pushed by the player
            if (checkMove(move + move_asked)){ // recursive call to check the next block until we have a wall, a free block or too much weight
                if (player->getWeight() > MAX_PLAYER_WEIGHT) return false; // too much weight for the player
                else { 
                    auto box = getBox(new_pos);
                    box->getAnimation().animate(new_pos, move_asked);
                    box->setPos(new_pos_box); // change the box position 
                    return true; 
                } 
            }else return false;
        }return true;
}

bool Board::checkTeleport(Point pos_teleporter){
    for (auto teleporter: teleporters){  // go through the teleporters
        if(teleporter->getPos() != pos_teleporter) {  // if the teleporter is not the one the player is using
            if (!getBox(teleporter->getPos())) return true; // if no box on the other teleporter
                return false; 
        }
    }
}

bool Board::isBlocked(shared_ptr<Block> box){
    Point pos_box = box->getPos();  // position of the box to check
    vector<Point> possible_moves;  // list of positions of cases to try to see if it's blocked
    vector<bool> blocked;  // list of booleans (true if blocked, false if not)
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_DOWN); // add position to try to the list
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_UP);
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_RIGHT);
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_LEFT);
    for (auto move: possible_moves){  // loop with all the elements of the liste next_case
        if (isInBoard(move)){  // if position (checked) is in the board
            shared_ptr<Block> box_on_case = getBox(move);  // ptr to a box or nullptr if no box on the case
            if (box_on_case) { // if box on case
                if (box_on_case->getWeight()==9) blocked.push_back(true);  // heavy box blocked by another heavy box
                else blocked.push_back(false);  // if it's a light box 
            }else if (getBlock(move)->getType()==Block::BlockType::wall) blocked.push_back(true); // boc blocked by a wall
            else blocked.push_back(false); // position does not block the box
        } else blocked.push_back(true);  // position is not on the board
    } return(blocked.at(0)|| blocked.at(1))&& (blocked.at(2)|| blocked.at(3));  // true if blocked at least once horizontally and once vertically
 }

 bool Board::failureDetection(){
    bool all_blocked = true;  // true if all boxes are blocked
    bool box_blocked;  // test each box at a time
    for (shared_ptr<Block> box: getBoxes()) {  // go through all the boxes of the board 
        box_blocked = isBlocked(box);  // test if box is blocked
        all_blocked = (all_blocked && box_blocked);
    }if (all_blocked) return true; // all boxes are blocked
    else return false;
 }
