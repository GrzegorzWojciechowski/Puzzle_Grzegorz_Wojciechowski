#include "gamemode.h"
/**
 * @brief GameMode::GameMode konstruktor
 */
GameMode::GameMode(){};
/**
 * @brief GameMode::~GameMode destruktor, wywołuje również destruktory obiektów Tile z tabeli puzzleTiles
 */
GameMode::~GameMode(){
    for(int i=0; i<numberOfTiles;i++){
        delete[] puzzleTiles[i];
    }
    delete[] puzzleTiles;
}
/**
 * @brief GameMode::startGame funkcja inicjalizująca rozgrywkę bazując na przekazanych danych, tworzy ikony na podstawie
 * wybranego przez użytkownika obrazka, tworzy tabelę obiektów typu tile odpowiedzialnych za logiczne odzwierciedlenie
 * stanu rozgrywki i przekazuje im ich startowe/docelowe wartości
 * @param _numberOfTiles wielkość pola
 * @param _imageFileName ścieżka do wybranego pliku png który będzie obrazkiem do ułożenia
 * @param _difficulty poziom trudności
 */
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
    QPixmap blackImage("");
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
/**
 * @brief GameMode::cropImageForButton funkcja tnąca obrazek na równe kwadraty i zwracająca ten o określonym położeniu
 * @param _x położenie lewego górnego rogu prostokąt służącego do cropowania w osi X
 * @param _y położenie lewego górnego rogu prostokąt służącego do cropowania w osi Y
 * @param _dimension rozmiar prostokąta służącego do cropowania
 * @param _image wybrany przez użytkownika obrazek
 * @return wycięta ikona
 */
QIcon GameMode::cropImageForButton(int _x, int _y, int _dimension, QPixmap _image){
    QPixmap work;
    QRect crop(_x,_y,_dimension,_dimension);
    work = _image.copy(crop);
    QIcon icon(work);
    return icon;
};

/**
 * @brief GameMode::mixTheTiles fukcja odpowiedzialna za mieszanie pól na początku gry, mieszanie polega na wykonaniu z pozycji ułożonego obrazka
     * określonej liczby losowych ruchów w celu pomieszania pól
 */
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

/**
 * @brief GameMode::passPushCheck funkcja odpowiedzialna za sprawdzenie czy kliknięte przez gracza pole znajduje się obok pola pustego
 * oraz jeśli tak to przypisuje wartości położeni pól do listy workingCords którą później wykorzystujemy
 * @param _x położenie X guzika klikniętego przez gracza
 * @param _y położenie Y guzika klikniętego przez gracza
 * @return jeśłi pole znajduje się obok pola pustego zwraca true jeśli nie false
 */
bool GameMode::passPushCheck(int _x, int _y){

    int rowOffsets[] = {-1,0,1,0};
    int collOffsets[] = {0,1,0,-1};
    workingCords.clear();
    for(int i=0;i<4;i++){
        int newRow = _x+rowOffsets[i];
        int newColl = _y+collOffsets[i];
        if(newRow>=0 && newRow<numberOfTiles && newColl>=0 && newColl<numberOfTiles){
            if(puzzleTiles[newRow][newColl].checkIfEmpty()){
                workingCords.push_back(puzzleTiles[newRow][newColl].getStartingXIndex());
                workingCords.push_back(puzzleTiles[newRow][newColl].getStartingYIndex());
                workingCords.push_back(puzzleTiles[_x][_y].getStartingXIndex());
                workingCords.push_back(puzzleTiles[_x][_y].getStartingYIndex());
                workingCords.push_back(newRow);
                workingCords.push_back(newColl);
                return true;
            }
        }
    }
    return false;
};
/**
 * @brief GameMode::getNewImageCords funkcja zwracająca listę położenia pól i położenia ikon
 * @return workingCords
 */
QList<int>  GameMode::getNewImageCords(){
    return workingCords;
};
/**
 * @brief GameMode::switchTiles funkcja odpowiedzialna za zamiana obiektów Tile w tabeli
 * @param _x położenie X jednego pola
 * @param _y położenie Y jednego pola
 * @param _a położenie X drugiego pola
 * @param _b położenie Y drugiego pola
 */
void GameMode::switchTiles(int _x, int _y, int _a, int _b){
    Tile helper = puzzleTiles[_x][_y];
    puzzleTiles[_x][_y] = puzzleTiles[_a][_b];
    puzzleTiles[_a][_b] = helper;

};
/**
 * @brief GameMode::checkWinCondition funkcja odpowiedzialna za sprawdzenie czy gracz wygrał grę
 * @return zwraca true jeśli wszystkie pola są na swojej pozycji i false jeśli którekolwiek nie jest
 */
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
/**
 * @brief GameMode::getNumberOfTiles funkcja zwracająca wielkość pola
 * @return numberOfTiles
 */
int GameMode::getNumberOfTiles(){
    return numberOfTiles;
};
/**
 * @brief GameMode::getTile
 * @param x położenie w tabeli w osi X
 * @param y położenie w tabeli w osi Y
 * @return poszukiwany obiekt
 */
Tile GameMode::getTile(int x, int y){
    return puzzleTiles[x][y];
};
/**
 * @brief GameMode::timeCheck funkcja stworzona do sprawdzania czy upłynął maksymalny czas gry, tu zaimplementowana
     * aby pokazać możliwości dziedziczenia
 * @param time aktualny czas rozgrywki
 * @return false zawsze
 */
bool GameMode::timeCheck(int time){
    return false;
}
