/**
 * @file timedgamemode.h
 * @brief Definiuje klasę TimedGameMode
 */
#ifndef TIMEDGAMEMODE_H
#define TIMEDGAMEMODE_H
#include "gamemode.h"
/**
 * @class Klasa TimedGameMode
 * @brief TimedGameMode to klasa rozwijająca możliwości klasy GameMode dodając fukcjonalności związane z czasem i wynikami
 */
class TimedGameMode : public GameMode
{
public:
    /**
     * @brief TimedGameMode konstruktor
     */
    TimedGameMode();
    /**
     * @brief startGame funkcja inicjalizująca rozgrywkę bazując na przekazanych danych, tworzy ikony na podstawie
     * wybranego przez użytkownika obrazka, tworzy tabelę obiektów typu tile odpowiedzialnych za logiczne odzwierciedlenie
     * stanu rozgrywki i przekazuje im ich startowe/docelowe wartości, dodatkowo wylicza maksymalny czas rozgrywki
     * @param _numberOfTiles wielkość pola
     * @param _imageFileName ścieżka do wybranego pliku png który będzie obrazkiem do ułożenia
     * @param _difficulty poziom trudności
     */
    void startGame(int _numberOfTiles, QString _imageFileName, int _difficulty) override;
    /**
     * @brief timeCheck funkcja sprawdza czy aktualny czas gry jest mniejszy bądź równy maksymalnemu
     * @param time atualny czas gry
     * @return zwraca true jeśli czas przekracza czas maksymalny false w innych wypadkach
     */
    bool timeCheck(int time) override;
    /**
     * @brief getMaxTime zwraca maksymalny możliwy czas gry
     * @return wartość pola maxTime
     */
    int getMaxTime();
    /**
     * @brief currentScore oblicza i zwraca aktualny wynik w grze
     * @param time aktualny czas gry
     * @return wynik
     */
    int currentScore(int time);

private:
    /**
     * @brief maxTime maksymalny czas wyliczony na podstawnie rozmiaru planszy
     */
    int maxTime;
};

#endif // TIMEDGAMEMODE_H
