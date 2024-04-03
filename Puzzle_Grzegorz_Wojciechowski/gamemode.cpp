#include "gamemode.h"
GameMode::GameMode(){};
void GameMode::startGame(int _numberOfTiles, QString _imageFileName, int _difficulty){
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
};

QIcon GameMode::cropImageForButton(int _x, int _y, int _dimension, QPixmap _image){
    QPixmap work;
    QRect crop(_x,_y,_dimension,_dimension);
    work = _image.copy(crop);
    QIcon icon(work);
    return icon;
};


void GameMode::mixTheTiles(){
    int moves = numberOfTiles*difficulty*10;
    srand(time(nullptr));
    int emptyRowIndex = numberOfTiles-1;
    int emptyCollIndex = numberOfTiles-1;
    int checkRow;
    int checkColl;
    int rowOffsets[] = {-1,0,1,0};
    int collOffsets[] = {0,1,0,-1};
    bool moved=false;
    for(int i=0;i<moves;i++){
        if(puzzleTiles[emptyRowIndex][emptyCollIndex].checkIfEmpty()!=true){
            moved=true;
        }
        while(moved==false){
            int direction = rand()%4;
            checkRow=emptyRowIndex+rowOffsets[direction];
            checkColl=emptyCollIndex+collOffsets[direction];
            if(checkRow<numberOfTiles&&checkRow>=0&&checkColl>=0&&checkColl<numberOfTiles){
                this->switchTiles(checkRow,checkColl,emptyRowIndex,emptyCollIndex);
                emptyRowIndex=checkRow;
                emptyCollIndex=checkColl;
                moved=true;
            }
        }
        moved=false;
    }
}







bool GameMode::passPushCheck(int _x, int _y){

    int rowOffsets[] = {-1,0,1,0};
    int collOffsets[] = {0,1,0,-1};

    for(int i=0;i<4;i++){
        int newRow = _x+rowOffsets[i];
        int newColl = _y+collOffsets[i];
        if(newRow>=0 && newRow<numberOfTiles && newColl>=0 && newColl<numberOfTiles){
            if(puzzleTiles[newRow][newColl].checkIfEmpty()){
                currentWorkedOnXCordStarting=puzzleTiles[newRow][newColl].getStartingXIndex();
                currentWorkedOnYCordStarting=puzzleTiles[newRow][newColl].getStartingYIndex();
                currentEmptyXCord=newRow;
                currentEmptyYCord=newColl;
                futureEmptyXCord = puzzleTiles[_x][_y].getStartingXIndex();
                futureEmptyYCord = puzzleTiles[_x][_y].getStartingYIndex();

                return true;
            }
        }
    }
    return false;
};

int  GameMode::getNewImageCords(int &_x, int &_y, int &_a, int &_b, int &_h, int &_g){
    _x = currentWorkedOnXCordStarting;
    _y = currentWorkedOnYCordStarting;
    _a = futureEmptyXCord;
    _b = futureEmptyYCord;
    _h = currentEmptyXCord;
    _g = currentEmptyYCord;
};

void GameMode::switchTiles(int _x, int _y, int _a, int _b){
    helper = puzzleTiles[_x][_y];
    puzzleTiles[_x][_y] = puzzleTiles[_a][_b];
    puzzleTiles[_a][_b] = helper;

};

bool GameMode::checkWinCondition(){
    for(int i=0;i<numberOfTiles;i++){
        for(int j=0;j<numberOfTiles;j++){
            if(puzzleTiles[i][j].checkIfPlacedRight(i,j)){

            }
            else{
                return false;
            }
        }
    }
    return true;
};
int GameMode::getNumberOfTiles(){
    return numberOfTiles;
};
Tile GameMode::getTile(int x, int y){
    return puzzleTiles[x][y];
};

bool GameMode::timeCheck(int time){

}
