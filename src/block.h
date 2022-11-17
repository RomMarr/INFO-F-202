#ifndef _BLOCK_H
#define _BLOCK_H

#include "stdio.h"
#include <string>
#include <FL/Fl.H>

using namespace std;

enum BlockType {wall, floor, target, box, teleporter}; // peut ajouter Block pour extérieur si on veut 

class Block {
    int weight;            // poids du Block
    Fl_Color color;        // couleur du Block 
    const int width = 50;  // largeur du Block
    const int height = 50; // hauteur du Block
    BlockType TypeBlock;
public:
    Block(int weight, Fl_Color color) ;
    void draw(int x, int y);
    void setWeight(int weight);
    void setColor(Fl_Color color);
    ~Block();
};

#endif