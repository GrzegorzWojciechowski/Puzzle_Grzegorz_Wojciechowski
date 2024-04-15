#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H
#include "QString"
#include "gamemode.h"
#include "freegamemode.h"
#include "timedgamemode.h"
#include "scoreboard.h"
class GameInstance
{
public:
    GameInstance();

    void gameStartFunction(int _numberOfTiles, QString _fileName, int gameModeType, int _difficulty);
    GameMode* currentGameMode;
    ScoreBoard* currentScoreBoard;

private:

};

#endif // GAMEINSTANCE_H
