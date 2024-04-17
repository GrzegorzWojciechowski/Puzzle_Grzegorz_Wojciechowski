/**
 * @file gameisntance.h
 * @brief Definiuje klasę GameInstance
*/


#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H
#include "QString"
#include "gamemode.h"
#include "freegamemode.h"
#include "timedgamemode.h"
#include "scoreboard.h"

/**
 * @class Klasa GameInstance
 * @brief Ta klasa jest połączeniem między logiką aplikacji a ui w wypadku modyfikowania na aplikację konsolową to tutaj znajdowałyby się funkcje
 * odpowiedzialne za input gracza i wyświetlanie planszy lub wyniku
 */
class GameInstance
{
public:
    /**
     * @brief Konstruktor klasy GameInstance
     */
    GameInstance();
    /**
     * @brief Destruktor klasy GameInstance
     */
    ~GameInstance();

    /**
     * @brief gameStartFunction inicjalizuje rozpoczęcie rozgrywki tworząc obiekt odpowiedniej klasy dziedziczącej po GameMode i przekazuje do niego dane
     * @param _numberOfTiles wielkość planszy
     * @param _fileName nazwa pliku zdjęcia wczytanego jako obrazek do układania
     * @param gameModeType wartość korespondująca z trybem gry
     * @param _difficulty poziom trudności
     */

    void gameStartFunction(int _numberOfTiles, QString _fileName, int gameModeType, int _difficulty);
    /**
     * @brief deleteGameMode odpowiedzialna za usuwanie obiektu GameMode i nadawanie mu wskaźnika do nullptr w celu uniknięcia dalszych błędów
     */
    void deleteGameMode();

    /**
     * @brief currentGameMode obiekt klasy GameMode lub klasy dziedziczącej odpowiedzialny za logikę gry
     */

    GameMode* currentGameMode=nullptr;

    /**
     * @brief currentScoreBoard obiekt odpowiedzialny za przetrzymywanie inforamcji związanych z tablicą wyników i jej modyfikowanie
     */

    ScoreBoard* currentScoreBoard;

private:

};

#endif // GAMEINSTANCE_H
