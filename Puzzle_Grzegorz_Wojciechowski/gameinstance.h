#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H
#include "QString"
#include "gamemode.h"
class GameInstance
{
public:
    GameInstance();

    void gameStartFunction(int _numberOfTiles, QString _fileName);
    GameMode currentGameMode;

private:

};

#endif // GAMEINSTANCE_H
