#include "tile.h"

Tile::Tile(){};

void Tile::setStartingValues(int _x, int _y, bool _isEmpty){
    originalIndexX = _x;
    originalIndexY = _y;

    isEmpty = _isEmpty;
};

bool Tile::checkIfEmpty(){
    return isEmpty;
};

int Tile::getStartingXIndex(){
    return originalIndexX;
};

int Tile::getStartingYIndex(){
    return originalIndexY;
};

bool Tile::checkIfPlacedRight(int _x, int _y){
    if(originalIndexX==_x&&originalIndexY==_y){
        return true;
    }
    else{
        return false;
    }
};
