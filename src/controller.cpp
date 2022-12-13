#include "controller.hpp"

#include "model.hpp"
#include "block.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "point.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;


Controller::Controller(shared_ptr<Board> board): board{board} {};

void Controller::selectLevel(int level_id) {
    board->setLevel("levels/" + to_string(level_id) + ".txt"); // set the level to correspond the file chosen
}

void Controller::keyHandler(int key_event){ // handle the keys pushed from the keyboard
    shared_ptr<Player> player = board->getPlayer();  //ptr to the player
    if (key_event == 32) board->resetLevel(); // key_event 32 is the space bar
    switch (key_event) {
    // REF https://www.fltk.org/doc-1.3/group__fl__events.html#ga12be48f03872da009734f557d1e761bc           
        case FL_Up:
            moveHandler(POSSIBLE_MOVE_UP);
            break;
        case FL_Down:
            moveHandler(POSSIBLE_MOVE_DOWN);
            break;
        case FL_Right:
            moveHandler(POSSIBLE_MOVE_RIGHT);
            break;
        case FL_Left:
            moveHandler(POSSIBLE_MOVE_LEFT);
            break;
        default:
            break;
    }player->setWeight(0);  // player doesn't push boxes anymore
    checkWin();
    checkLose();
}

void Controller::moveHandler(const Point &move){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    Point pos_player = player->getPos();  // position of the player
    player->setMoveAsked(move); // change the move asked by the player
    if (checkMove(move)){  // if the move is authorized
        if (!player->isTeleported()) { // if the player do a normal move
            Point move_asked = player->getMoveAsked();
            Point new_pos = pos_player + move_asked;
            player->setPos(new_pos); // change de position of the player
        } else {
            Point new_pos = pos_player + move;
            board->teleport(new_pos); // check if the play can teleport and does it if he can
            player->changeTeleported();
        }
        player->addStep();
    }; 
}


bool Controller::checkMove(Point move){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    Point new_pos = player->getPos() + move; // new possible position of the player (not checked yet)

    if (!board->isInBoard(new_pos)) return false; 
    // check if the player will not leave the board with its movement
    if (player->getWeight()> MAX_PLAYER_WEIGHT) return false;
    // A player can push max a weight lesser than 10
    
    Block::BlockType destination_type = board->getBlock(new_pos)->getType();  
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

bool Controller::checkMoveTeleport(Point move){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    Point pos_player = player->getPos();  // position of the player
    Point new_pos = pos_player + move; // new possible position of the player (not checked yet)
    Point move_asked = player->getMoveAsked();  // movement add to the player's position to get his new position
    Point new_pos_box = new_pos + move_asked; // new possible position of the box (not checked yet)
    shared_ptr<Block> box_on_move = board->getBox(new_pos);  // ptr to the box if there is one, nullptr if not
    if (box_on_move){ // if box on the new_pos of the player
            player->setWeight(player->getWeight()+ box_on_move->getWeight()); // add the weight of the box
            if (checkMove(move + move_asked)){  // if move authorized
                if (board->getBlock(pos_player+ move_asked)->getType()==Block::BlockType::teleporter){
                    // type of the block of the new_pos is a teleporter
                    board->getBox(new_pos)->setPos(new_pos_box); // change de position of the box
                    if (checkTeleport(new_pos)) { // if player can teleport
                        player->changeTeleported(); // teleported = true
                        return true;
                    }return false;
                }board->getBox(new_pos)->setPos(new_pos_box); // change de position of the box
            } 
    }if (board->getBlock(pos_player+ move_asked)->getType()==Block::BlockType::teleporter){
    // type of the block of the new_pos is a teleporter
        if (checkTeleport(new_pos)) { // if player can teleport
            player->changeTeleported(); // teleported = true
            return true;
        }return false;
    }return true;
}

bool Controller::checkMoveNormal(Point move){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    Point pos_player = player->getPos();  // position of the player
    Point new_pos = pos_player + move; // new possible position of the player (not checked yet)
    Point move_asked = player->getMoveAsked();  // movement add to the player's position to get his new position
    Point new_pos_box = new_pos + move_asked; // new possible position of the box (not checked yet)
    shared_ptr<Block> box_on_move = board->getBox(new_pos);  // ptr to the box if there is one, nullptr if not
    if (box_on_move){  // check if ptr != nullptr
            player->setWeight(player->getWeight()+ box_on_move->getWeight()); // add the weight of the box pushed by the player
            if (checkMove(move + move_asked)){ // recursive call to check the next block until we have a wall, a free block or too much weight
                if (player->getWeight() > MAX_PLAYER_WEIGHT) return false; // too much weight for the player
                else { 
                    board->getBox(new_pos)->setPos(new_pos_box); // change the box position 
                    return true; 
                } 
            }else return false;
        }return true;
}

bool Controller::checkTeleport(Point pos_teleporter){
    vector<shared_ptr<Block>> teleporters = board->getTeleporters(); //vector of ptr of teleporters
    for (auto teleporter: teleporters){  // go through the teleporters
        if(teleporter->getPos() != pos_teleporter) {  // if the teleporter is not the one the player is using
            if (! board->getBox(teleporter->getPos())) return true; // if no box on the other teleporter
                return false; 
        }
    }
}

bool Controller::isBlocked(shared_ptr<Block> box){
    Point pos_box = box->getPos();  // position of the box to check
    vector<Point> possible_moves;  // list of positions of cases to try to see if it's blocked
    vector<bool> blocked;  // list of booleans (true if blocked, false if not)
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_DOWN); // add position to try to the list
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_UP);
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_RIGHT);
    possible_moves.push_back(pos_box + POSSIBLE_MOVE_LEFT);
    for (auto move: possible_moves){  // loop with all the elements of the liste next_case
        if (board->isInBoard(move)){  // if position (checked) is in the board
            shared_ptr<Block> box_on_case = board->getBox(move);  // ptr to a box or nullptr if no box on the case
            if (box_on_case) { // if box on case
                if (box_on_case->getWeight()==9) blocked.push_back(true);  // heavy box blocked by another heavy box
                else blocked.push_back(false);  // if it's a light box 
            }else if (board->getBlock(move)->getType()==Block::BlockType::wall) blocked.push_back(true); // boc blocked by a wall
            else blocked.push_back(false); // position does not block the box
        } else blocked.push_back(true);  // position is not on the board
    } return(blocked.at(0)|| blocked.at(1))&& (blocked.at(2)|| blocked.at(3));  // true if blocked at least once horizontally and once vertically
 }

 bool Controller::failureDetection(){
    bool all_blocked = true;  // true if all boxes are blocked
    bool box_blocked;  // test each box at a time
    for (shared_ptr<Block> box: board->getBoxes()) {  // go through all the boxes of the board 
        box_blocked = isBlocked(box);  // test if box is blocked
        all_blocked = (all_blocked && box_blocked);
    }if (all_blocked) return true; // all boxes are blocked
    else return false;
 }

bool Controller::checkLose(){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    return (player->getSteps() >= board->getMaxSteps() || failureDetection()); // true if game over

}

bool Controller::checkWin(){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    if (board->nbBoxOnTarget() != static_cast<int>(board->getBoxes().size())) return false; // if not all boxes are on a target
    if (board->getBestSteps() == -1 || board->getBestSteps() > player->getSteps()) board->writeBestSteps(); // if best steps has been beaten
    return true;
}