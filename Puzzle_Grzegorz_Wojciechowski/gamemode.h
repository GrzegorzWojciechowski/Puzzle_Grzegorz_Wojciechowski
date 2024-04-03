#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "qicon.h"
#include "qpixmap.h"
#include "Tile.h"

class GameMode
{
public:
    GameMode();
    virtual void startGame(int _numberOfTiles, QString _imageFileName, int _difficulty);
    bool passPushCheck(int _x, int _y);
    int getNewImageCords(int &_x, int &_y, int &_a, int &_b, int &_h, int &_g);
    QIcon **buttonIcons;
    QIcon **originalIcons;
    Tile **puzzleTiles;
    void switchTiles(int _x, int _y, int _a, int _b);
    virtual bool checkWinCondition();
    virtual bool timeCheck(int time);
    int getNumberOfTiles();
    Tile getTile(int x, int y);
    void mixTheTiles();
//protected:
    int numberOfTiles;
    int difficulty;
    QPixmap chosenImage;
    QPixmap black;
    QIcon cropImageForButton(int _x, int _y, int _dimension, QPixmap _image);
    int currentWorkedOnXCordStarting;
    int currentWorkedOnYCordStarting;
    int currentEmptyXCord;
    int currentEmptyYCord;
    int futureEmptyXCord;
    int futureEmptyYCord;
    Tile helper;

};

#endif // GAMEMODE_H
