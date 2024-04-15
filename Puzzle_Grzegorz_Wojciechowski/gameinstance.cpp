#include "gameinstance.h"
#include "scoreboard.h"

GameInstance::GameInstance() {
    currentScoreBoard = new ScoreBoard;
    currentScoreBoard->readScores();
}

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
