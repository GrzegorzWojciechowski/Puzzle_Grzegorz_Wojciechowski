#include "timedgamemode.h"

TimedGameMode::TimedGameMode() {}

bool TimedGameMode::timeCheck(int time){
    //maxTime = numberOfTiles*5;
    if(time>maxTime){
        return true;
    }
    else{
        return false;
    }
}
void TimedGameMode::startGame(int _numberOfTiles, QString _imageFileName, int _difficulty){
    maxTime=_numberOfTiles*20;
    numberOfTiles = _numberOfTiles;
    difficulty=_difficulty;
    buttonIcons = new QIcon*[_numberOfTiles];
    originalIcons = new QIcon*[_numberOfTiles];
    for(int i=0;i<_numberOfTiles;i++){
        buttonIcons[i] = new QIcon[_numberOfTiles];
        originalIcons[i] = new QIcon[_numberOfTiles];
    }
    QPixmap image(_imageFileName);
    chosenImage = image;
    QPixmap blackImage("C:/Users/grzeg/Documents/Qt_C-/black.png");
    black = blackImage;
    int dimension = 512/_numberOfTiles-4;
    for(int i=0; i<_numberOfTiles; i++){
        for(int j=0; j<_numberOfTiles; j++){
            if(i!=_numberOfTiles-1||j!=_numberOfTiles-1){
                buttonIcons[i][j]=cropImageForButton(j*dimension,i*dimension,dimension, chosenImage);
                originalIcons[i][j] = buttonIcons[i][j];
            }
            else{
                buttonIcons[i][j]=cropImageForButton(j*dimension,i*dimension,dimension, black);
                originalIcons[i][j]=cropImageForButton(j*dimension,i*dimension,dimension, chosenImage);
            }
        }
    }
    puzzleTiles = new Tile*[_numberOfTiles];
    for(int i=0;i<_numberOfTiles;i++){
        puzzleTiles[i] = new Tile[_numberOfTiles];
    }
    for(int i=0; i<_numberOfTiles; i++){
        for(int j=0; j<_numberOfTiles; j++){
            if(i!=_numberOfTiles-1||j!=_numberOfTiles-1){
                puzzleTiles[i][j].setStartingValues(i,j,false);

            }
            else{
                puzzleTiles[i][j].setStartingValues(i,j,true);

            }
        }
    }
}

int TimedGameMode::getMaxTime(){
    return maxTime;
}

int TimedGameMode::currentScore(int time){
    return numberOfTiles*100+difficulty*100-time*10;
}
