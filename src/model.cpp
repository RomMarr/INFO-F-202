#include "model.h"
#include <iostream>
#include <fstream>
#include <FL/Fl.H>

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.



Block::Block(int weight, Fl_Color color, BlockType type):weight{weight}, color{color},type{type}{}

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

void Block::setPos(int new_posX, int new_posY){
    get<0>(pos) = new_posX;
    get<1>(pos)= new_posY;
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




// fct incomplete voir ci dessous
void Board::read_file(string fileName){
    string line;
    ifstream file(fileName);
    if (file.is_open()) {  // ouvre le fichier txt contenant le board
        while (getline(file, line)) { // la variable line contient maintenant la ligne lue
            // A FAIRE : incrémenté matrice
        }file.close();  // ferme le fichier txt
    };
}

bool Board::box_on_pos(tuple<int, int> pos_actual){
    for (auto i: pos_box){
        if (i.getPos() == pos_actual) return true;
    }return false;
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

