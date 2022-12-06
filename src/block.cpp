#include "block.hpp"

#include "constants.hpp"
#include "point.hpp"

#include <FL/Fl.H>


Block::Block(BlockType type): type{type} {
    if (type == BlockType::heavy_box) {
        this->setWeight(HEAVY_BOX_WEIGHT);
    } else if (type == BlockType::light_box) {
        this->setWeight(LIGHT_BOX_WEIGHT);
    }
}

void Block::setWeight(int new_weight){
    weight = new_weight; 
}

void Block::setType(BlockType new_type){
    type = new_type;
}

void Block::setIdColor(int new_id_color){
    id_color = new_id_color;
}

void Block::setPos(Point new_position){
    pos = new_position;
}

Point Block::getPos(){
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
        case (BlockType::wall): return BLOCK_WALL_COLOR; break;
        case (BlockType::floor): return BLOCK_FLOOR_COLOR;  break;
        case (BlockType::target): return BLOCK_TARGET_COLOR; break;
        case (BlockType::teleporter): return BLOCK_TELEPORTER_COLOR; break;
        case (BlockType::light_box): return BLOCK_LIGHT_BOX_COLOR; break;
        default: {
            if (type == Block::BlockType::heavy_box){
                return BLOCK_HEAVY_BOX_COLORS.at(id_color); break;
            }return fl_rgb_color(100, 100, 100); break;
            }
    }
}

Block::BlockType Block::getType(){
    return type;
}