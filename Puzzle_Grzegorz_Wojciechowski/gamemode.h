/**
 * @file gamemode.h
 *
 */

#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "qicon.h"
#include "qpixmap.h"
#include "Tile.h"
/**
 * @class Klasa GameMode
 * @brief Klasa zajmuje się logiką gry i niestety również przygotowywaniem i przchowywaniem danych związanych z
 * wizualizacją
 */
class GameMode
{
public:
    /**
     * @brief GameMode konstruktor
     */
    GameMode();
    /**
     * @brief ~GameMode destruktor
     */
    ~GameMode();
    /**
     * @brief startGame funkcja inicjalizująca rozgrywkę bazując na przekazanych danych, tworzy ikony na podstawie
     * wybranego przez użytkownika obrazka, tworzy tabelę obiektów typu tile odpowiedzialnych za logiczne odzwierciedlenie
     * stanu rozgrywki i przekazuje im ich startowe/docelowe wartości
     * @param _numberOfTiles wielkość pola
     * @param _imageFileName ścieżka do wybranego pliku png który będzie obrazkiem do ułożenia
     * @param _difficulty poziom trudności
     */
    virtual void startGame(int _numberOfTiles, QString _imageFileName, int _difficulty);
    /**
     * @brief passPushCheck funkcja odpowiedzialna za sprawdzenie czy kliknięte przez gracza pole znajduje się obok pola pustego
     * oraz jeśli tak to przypisuje wartości położeni pól do listy workingCords którą później wykorzystujemy do wykonania ruchu
     * @param _x położenie X guzika klikniętego przez gracza
     * @param _y położenie Y guzika klikniętego przez gracza
     * @return jeśłi pole znajduje się obok pola pustego zwraca true jeśli nie false
     */
    bool passPushCheck(int _x, int _y);
    /**
     * @brief getNewImageCords funkcja zwracająca listę położenia pól i położenia ikon
     * @return workingCords
     */
    QList<int> getNewImageCords();
    /**
     * @brief buttonIcons tabela ikon wykorzystanych podczas gry
     */
    QIcon **buttonIcons;
    /**
     * @brief originalIcons tabela oryginalnego położenia ikon wykorzystanych podczas gry
     */
    QIcon **originalIcons;
    /**
     * @brief puzzleTiles tabela obiektów typu tile, położenie obiektów w tej tabeli odzwierciedla położenie pól na planszy
     */
    Tile **puzzleTiles;
    /**
     * @brief switchTiles funkcja odpowiedzialna za zamiana obiektów Tile w tabeli
     * @param _x położenie X jednego pola
     * @param _y położenie Y jednego pola
     * @param _a położenie X drugiego pola
     * @param _b położenie Y drugiego pola
     */
    void switchTiles(int _x, int _y, int _a, int _b);
    /**
     * @brief checkWinCondition funkcja odpowiedzialna za sprawdzenie czy gracz wygrał grę
     * @return zwraca true jeśli wszystkie pola są na swojej pozycji i false jeśli którekolwiek nie jest
     */
    virtual bool checkWinCondition();
    /**
     * @brief timeCheck funkcja stworzona do sprawdzania czy upłynął maksymalny czas gry, tu zaimplementowana
     * aby pokazać możliwości dziedziczenia
     * @param time aktualny czas rozgrywki
     * @return false zawsze
     */
    virtual bool timeCheck(int time);
    /**
     * @brief getNumberOfTiles funkcja zwracająca wielkość pola
     * @return numberOfTiles
     */
    int getNumberOfTiles();
    /**
     * @brief getTile funkcja zwracająca obiekt Tile o określonym położeniu w tabeli puzzleTiles
     * @param x położenie w tabeli w osi X
     * @param y położenie w tabeli w osi Y
     * @return poszukiwany obiekt
     */
    Tile getTile(int x, int y);
    /**
     * @brief mixTheTiles fukcja odpowiedzialna za mieszanie pól na początku gry, mieszanie polega na wykonaniu z pozycji ułożonego obrazka
     * określonej liczby losowych ruchów w celu pomieszania pól
     */
    void mixTheTiles();
protected:
    /**
     * @brief numberOfTiles rozmiar planszy
     */
    int numberOfTiles;
    /**
     * @brief difficulty poziom trudności
     */
    int difficulty;
    /**
     * @brief chosenImage Pixmapa wybranego przez gracza obrazka
     */
    QPixmap chosenImage;
    /**
     * @brief black Pixmapa pustego pola (bez większego zastosowania pozostawiona do rozbudowy aplikacji)
     */
    QPixmap black;
    /**
     * @brief cropImageForButton funkcja tnąca obrazek na równe kwadraty i zwracająca ten o określonym położeniu
     * @param _x położenie lewego górnego rogu prostokąt służącego do cropowania w osi X
     * @param _y położenie lewego górnego rogu prostokąt służącego do cropowania w osi Y
     * @param _dimension rozmiar prostokąta służącego do cropowania
     * @param _image wybrany przez użytkownika obrazek
     * @return wycięta ikona
     */
    QIcon cropImageForButton(int _x, int _y, int _dimension, QPixmap _image);
    /**
     * @brief workingCords lista intów zwracana w celu zmiany położenia pól na planszy
     */
    QList<int> workingCords;

};

#endif // GAMEMODE_H
