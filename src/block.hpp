#ifndef _BLOCK_H
#define _BLOCK_H

#include "stdio.h"
#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>
#include <tuple>


using namespace std;

// le model en MVC : a une représentation du plateau, 
// ainsi que la gestion des règles (dans un autre fichier) -> coup possible ou non.

class Block {
public:
    enum BlockType { wall, floor, target, box, light_box, teleporter }; // peut ajouter Block pour extérieur si on veut
private:    
    const int width = 50;  // largeur du Block
    const int height = 50; // hauteur du Block 
    BlockType type;
    int weight;       // poids du Block
    tuple<int,int> pos;    // position du Block
public:
    Block(BlockType type) ;
    void setWeight(int weight);
    void setType(BlockType new_type);
    void setPos(tuple<int, int> new_position);
    tuple<int, int> getPos();
    int getWeight();
    int getWidth();
    int getHeight();
    Fl_Color getColor();
    BlockType getType();
};

#endif