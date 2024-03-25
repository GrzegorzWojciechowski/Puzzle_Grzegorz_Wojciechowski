#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile();
    void setStartingValues(int _x, int _y, bool _isEmpty);
    bool checkIfEmpty();
    int getStartingXIndex();
    int getStartingYIndex();
    bool checkIfPlacedRight(int _x, int _y);
private:
    int originalIndexX;
    int originalIndexY;
    bool isEmpty;

};

#endif // TILE_H
