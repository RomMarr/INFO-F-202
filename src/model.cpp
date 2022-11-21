#include "model.h"
#include <iostream>
#include <fstream>

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.



// fct incomplete voir ci dessous
void Board::file_to_matrix(string fileName){
    string line;
    ifstream file(fileName);
    if (file.is_open()) {  // ouvre le fichier txt contenant le board
        while (getline(file, line)) { // la variable line contient maintenant la ligne lue
            // A FAIRE : incrémenté matrice
        }file.close();  // ferme le fichier txt
    }
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

