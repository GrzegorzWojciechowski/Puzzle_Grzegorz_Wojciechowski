#include "timedgamemode.h"

/**
 * @brief TimedGameMode::TimedGameMode konstruktor
 */
TimedGameMode::TimedGameMode() {}
/**
 * @brief TimedGameMode::timeCheck funkcja sprawdza czy aktualny czas gry jest mniejszy bądź równy maksymalnemu
 * @param time atualny czas gry
 * @return zwraca true jeśli czas przekracza czas maksymalny false w innych wypadkach
 */
bool TimedGameMode::timeCheck(int time){
    if(time>maxTime){
        return true;
    }
    else{
        return false;
    }
}
/**
 * @brief TimedGameMode::startGame funkcja inicjalizująca rozgrywkę bazując na przekazanych danych, tworzy ikony na podstawie
 * wybranego przez użytkownika obrazka, tworzy tabelę obiektów typu tile odpowiedzialnych za logiczne odzwierciedlenie
  * stanu rozgrywki i przekazuje im ich startowe/docelowe wartości, dodatkowo wylicza maksymalny czas rozgrywki
 * @param _numberOfTiles wielkość pola
 * @param _imageFileName ścieżka do wybranego pliku png który będzie obrazkiem do ułożenia
 * @param _difficulty poziom trudności
 */
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
}
/**
 * @brief TimedGameMode::getMaxTime zwraca maksymalny możliwy czas gry
 * @return wartość pola maxTime
 */
int TimedGameMode::getMaxTime(){
    return maxTime;
}
/**
 * @brief TimedGameMode::currentScore oblicza i zwraca aktualny wynik w grze
 * @param time aktualny czas gry
 * @return wynik
 */
int TimedGameMode::currentScore(int time){
    return numberOfTiles*200+difficulty*100-time*10;
}
