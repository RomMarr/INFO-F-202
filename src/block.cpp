#include "block.hpp"
#include <FL/Fl.H>


Block::Block(BlockType type): type{type} {
    if (type == BlockType::box) {
        this->setWeight(9);
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
        case (BlockType::box): return fl_rgb_color(102, 51, 0); break;
        case (BlockType::light_box): return fl_rgb_color(204, 102, 0); break;
        case (BlockType::floor): return fl_rgb_color(224, 224, 224);  break;
        case (BlockType::target): return fl_rgb_color(255, 204, 153); break;
        case (BlockType::teleporter): return fl_rgb_color(153, 0, 153); break;
        default: return fl_rgb_color(100, 100, 100); break;
    }
}

Block::BlockType Block::getType(){
    return type;
}