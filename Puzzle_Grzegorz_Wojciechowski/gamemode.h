#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "qicon.h"
#include "qpixmap.h"
#include "Tile.h"

class GameMode
{
public:
    GameMode();
    void startGame(int _numberOfTiles, QString _imageFileName);
    bool passPushCheck(int _x, int _y);
    int getNewImageCords(int &_x, int &_y, int &_a, int &_b, int &_h, int &_g);
    QIcon **buttonIcons;
    Tile **puzzleTiles;
    void switchTiles(int _x, int _y, int _a, int _b);
    bool checkWinCondition();

private:
    int numberOfTiles;

    QPixmap chosenImage;
    QPixmap black;
    QIcon cropImageForButton(int _x, int _y, int _dimension, QPixmap _image);
    int currentWorkedOnXCordStarting;
    int currentWorkedOnYCordStarting;
    int currentWorkedOnXCord;
    int currentWorkedOnYCord;
    int futureEmptyXCord;
    int futureEmptyYCord;
    Tile helper;

};

#endif // GAMEMODE_H
