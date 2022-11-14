#include "bloc.h"

Bloc::Bloc() 

virtual void Bloc::draw() const=0;

virtual void Bloc::setWeight(int new_weight) const=0;

virtual void Bloc::setColor(string color) const=0;

Target::Target():weight{-1}, color{"red"}

void Target::setWeight(int new_weight){
    weight = new_weight; }

void Target::setColor(string new_color){
    color = new_color; }

void Target::draw(){

}

Wall::Wall():weight{10}, color{"black"}

void Wall::setWeight(int new_weight){
    weight = new_weight; }

void Wall::setColor(string new_color){
    color = new_color; }

void Wall::draw(){
    
}

Floor::Floor():weight{-1}, color{"gray"}

void Floor::setWeight(int new_weight){
    weight = new_weight; }

void Floor::setColor(string new_color){
    color = new_color; }

void Floor::draw(){
    
}

Box::Box():weight{6}, color{"brown"}

void Box::setWeight(int new_weight){
    weight = new_weight; }

void Box::setColor(string new_color){
    color = new_color; }

void Box::draw(){
    
}

void Box::move(){

}

Teleporter::Teleporter():weight{-1}, color{"purple"}

void Teleporter::setWeight(int new_weight){
    weight = new_weight; }

void Teleporter::setColor(string new_color){
    color = new_color; }

void Teleporter::draw(){
    
}

void Teleporter::teleport(){

}