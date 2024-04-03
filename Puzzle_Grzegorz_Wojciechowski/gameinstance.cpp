#include "gameinstance.h"

GameInstance::GameInstance() {}

void GameInstance::gameStartFunction(int _numberOfTiles, QString _fileName, int gameModeType, int _difficulty){
    if(gameModeType==0){
        //FreeGameMode gm;
        currentGameMode = new FreeGameMode;
    }
    else{
        //TimedGameMode gm;
        currentGameMode = new TimedGameMode;
    }
    currentGameMode->startGame(_numberOfTiles,_fileName,_difficulty);

};
