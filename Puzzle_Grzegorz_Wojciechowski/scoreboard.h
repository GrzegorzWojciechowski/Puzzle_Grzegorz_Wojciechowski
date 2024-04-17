/**
 * @file scoreboard.h
 * @brief Definuje klasę ScoarBoard
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "QList"

/**
 * @class Klasa ScoarBoard
 * @brief To klasa odpowiedzialna za wczytywanie wykników z pliku i zapisywanie nowych lub zmodyfikowanych
 * wyników do pliku
 */

class ScoreBoard
{
public:

    /**
     * @brief ScoreBoard konstruktor klasy ScoarBoard
     */
    ScoreBoard();

    /**
     * @brief writeScores funkcja odpowiedzialna za zapisywanie listy akualnych wyników do pliku
     */

    void writeScores();

    /**
     * @brief updateScores funkcja odpowiedzialna za sprawdzanie czy nowy wynik znajduje się w top 5 wyników
     * @param newScore nowy wynik
     * @return wartość bool true jeśli wynik znajduje się w top 5 false jeśli nie
     */

    bool updateScores(int newScore);

    /**
     * @brief readScores wczytuje wyniki z pliku
     */

    void readScores();

    /**
     * @brief getScoreListSize zwraca rozmiar tablicy wyników
     * @return rozmiar tablicy wyników
     */

    int getScoreListSize();

    /**
     * @brief getScore zwraca wynik znajdujący się na określonej pozycji listy wyników
     * @param scorePlace miejsce w liście wynikow
     * @return wynik
     */

    int getScore(int scorePlace);

private:
    /**
     * @brief scores lista wartości typu int zawierająca wyniki
     */
    QList<int> scores;

};

#endif // SCOREBOARD_H
