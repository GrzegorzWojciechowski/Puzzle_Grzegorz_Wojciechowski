#include "gameinstance.h"

GameInstance::GameInstance() {}

void GameInstance::gameStartFunction(int _numberOfTiles, QString _fileName){
    currentGameMode.startGame(_numberOfTiles,_fileName);

};
