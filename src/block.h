#ifndef _BLOCK_H
#define _BLOCK_H

#include "stdio.h"
#include <string>
#include <FL/Fl.H>

using namespace std;


class Block {
public:
    enum BlockType {wall, floor, target, box, teleporter}; // peut ajouter Block pour extérieur si on veut
private:
    int weight;            // poids du Block
    Fl_Color color;        // couleur du Block 
    const int width = 50;  // largeur du Block
    const int height = 50; // hauteur du Block 
    BlockType type;
public:
    Block(int weight, Fl_Color color, BlockType type) ;
    void draw(int x, int y);
    void setWeight(int weight);
    void setColor(Fl_Color color);
    void setType(BlockType new_type);
    int getWeight();
    int getWidth();
    int getHeight();
    Fl_Color getColor();
    BlockType getType();
    //~Block();
};

#endif