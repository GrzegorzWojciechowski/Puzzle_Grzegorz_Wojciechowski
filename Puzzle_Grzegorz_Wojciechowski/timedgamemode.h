#ifndef TIMEDGAMEMODE_H
#define TIMEDGAMEMODE_H
#include "gamemode.h"

class TimedGameMode : public GameMode
{
public:
    TimedGameMode();
    void startGame(int _numberOfTiles, QString _imageFileName, int _difficulty) override;
    bool timeCheck(int time) override;
    int getMaxTime();

private:
    int maxTime;
};

#endif // TIMEDGAMEMODE_H
