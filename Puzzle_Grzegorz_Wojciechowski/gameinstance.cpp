#include "gameinstance.h"
#include "scoreboard.h"

/**
 * @brief GameInstance::GameInstance konstruktor obiektu, wtrakcie działania funkcji tworzony jest obiek typu ScoreBoard i wczytywane są
 * do niego wartości z pliku przetrzymującego wcześniejsze wyniki
 */

GameInstance::GameInstance() {
    currentScoreBoard = new ScoreBoard;
    currentScoreBoard->readScores();
}

/**
 * @brief GameInstance::~GameInstance destruktor obiektu, wywołuje destruktory GameMode i ScoreBoard
 */

GameInstance::~GameInstance(){
    if(currentGameMode!=nullptr)
        delete currentGameMode;
    delete currentScoreBoard;

}

/**
 * @brief GameInstance::gameStartFunction inicjalizuje rozpoczęcie rozgrywki tworząc obiekt odpowiedniej klasy dziedziczącej po GameMode i przekazuje
 * do niego dane oraz wywołuje funkcję startGame klasy GameMode
 * @param _numberOfTiles wielkość planszy
 * @param _fileName nazwa pliku zdjęcia wczytanego jako obrazek do układania
 * @param gameModeType wartość korespondująca z trybem gry
 * @param _difficulty poziom trudności
 */

void GameInstance::gameStartFunction(int _numberOfTiles, QString _fileName, int gameModeType, int _difficulty){
    if(gameModeType==0){

        currentGameMode = new GameMode;
    }
    else{

        currentGameMode = new TimedGameMode;
    }
    currentGameMode->startGame(_numberOfTiles,_fileName,_difficulty);


};
/**
 * @brief GameInstance::deleteGameMode odpowiedzialna za usuwanie obiektu GameMode i nadawanie mu wskaźnika do nullptr w celu uniknięcia dalszych błędów
 */
void GameInstance::deleteGameMode(){
    delete currentGameMode;
    currentGameMode=nullptr;
}
