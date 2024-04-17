/**
 * @file tile.h
 * @brief Definiuja klasę Tile
 */

#ifndef TILE_H
#define TILE_H

/**
 * @brief The Tile class klasa odpowiedzialna za prztrzymywanie informacji o kafelkach planszy
 */

class Tile
{
public:
    /**
     * @brief Tile konstruktor klasy
     */
    Tile();

    ~Tile();
    /**
     * @brief setStartingValues funkcja przypisująca informację wstępne kafelka
     * @param _x położenie w X
     * @param _y położenie w Y
     * @param _isEmpty czy jest to psuty kafelek
     */

    void setStartingValues(int _x, int _y, bool _isEmpty);

    /**
     * @brief checkIfEmpty fukcja sprawdza czy kafelek jest kafelkiem pustym
     * @return wartość pola isEmpty
     */

    bool checkIfEmpty();

    /**
     * @brief getStartingXIndex funkcja zwraca docelowe/początkowe położenie w X
     * @return wartość pola originalIndexX
     */
    int getStartingXIndex();
    /**
     * @brief getStartingYIndex funkcja zwraca docelowe/początkowe położenie w Y
     * @return wartość pola originalIndexY
     */
    int getStartingYIndex();
    /**
     * @brief checkIfPlacedRight fukcja sprawdza czy przekazane wartości położenia są wartościami końcowymi dla kafela
     * @param _x aktualne położenie w tabeli zawartej w obiekcie GameMode w X
     * @param _y aktualne położenie w tabeli zawartej w obiekcie GameMode w Y
     * @return jeśli położenie poprwane zwraca true jesli nie zwraca false
     */
    bool checkIfPlacedRight(int _x, int _y);
private:
    /**
     * @brief originalIndexX wartość położenia w X (docelowe miejsce kafelka)
     */
    int originalIndexX;
    /**
     * @brief originalIndexY wartość położenia w Y (docelowe miejsce kafelka)
     */
    int originalIndexY;
    /**
     * @brief isEmpty definiuje czy kafelek jest pusty
     */
    bool isEmpty;

};

#endif // TILE_H
