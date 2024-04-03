#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H
#include "QString"
#include "gamemode.h"
#include "freegamemode.h"
#include "timedgamemode.h"
class GameInstance
{
public:
    GameInstance();

    void gameStartFunction(int _numberOfTiles, QString _fileName, int gameModeType, int _difficulty);
    GameMode* currentGameMode;

private:

};

#endif // GAMEINSTANCE_H
