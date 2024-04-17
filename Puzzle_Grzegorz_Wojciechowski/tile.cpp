#include "tile.h"
/**
 * @brief Tile::Tile konstuktor
 */
Tile::Tile(){};

Tile::~Tile(){};
/**
 * @brief Tile::setStartingValues funkcja przypisująca informację wstępne kafelka
 * @param _x położenie w X
 * @param _y położenie w Y
 * @param _isEmpty czy jest to psuty kafelek
 */
void Tile::setStartingValues(int _x, int _y, bool _isEmpty){
    originalIndexX = _x;
    originalIndexY = _y;

    isEmpty = _isEmpty;
};
/**
 * @brief Tile::checkIfEmpty fukcja sprawdza czy kafelek jest kafelkiem pustym
 * @return wartość pola isEmpty
 */
bool Tile::checkIfEmpty(){
    return isEmpty;
};
/**
 * @brief Tile::getStartingXIndex funkcja zwraca docelowe/początkowe położenie w X
 * @return wartość pola originalIndexX
 */
int Tile::getStartingXIndex(){
    return originalIndexX;
};
/**
 * @brief Tile::getStartingYIndex funkcja zwraca docelowe/początkowe położenie w Y
 * @return wartość pola originalIndexY
 */
int Tile::getStartingYIndex(){
    return originalIndexY;
};
/**
 * @brief Tile::checkIfPlacedRight fukcja sprawdza czy przekazane wartości położenia są wartościami końcowymi dla kafela
 * @param _x aktualne położenie w tabeli zawartej w obiekcie GameMode w X
 * @param _y aktualne położenie w tabeli zawartej w obiekcie GameMode w Y
 * @return jeśli położenie poprwane zwraca true jesli nie zwraca false
 */
bool Tile::checkIfPlacedRight(int _x, int _y){
    if(originalIndexX==_x&&originalIndexY==_y){
        return true;
    }
    else{
        return false;
    }
};
