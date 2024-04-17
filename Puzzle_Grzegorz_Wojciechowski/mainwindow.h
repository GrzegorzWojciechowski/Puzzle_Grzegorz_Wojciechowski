/**
 * @file mainwindow.h
 * @brief Definiuje klasę MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameinstance.h"
#include "qpushbutton.h"
#include "QTimer"
#include "QLabel"
QT_BEGIN_NAMESPACE
namespace Ui {
/**
 * @class Klasa MainWindow
 * @brief Klasa odpowiedzialna z wyświetlanie UI aplikacji i część jej logiki związaną bezpośrednio z interakcją z graczem
 */
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow kostruktor
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief setCurrentGameInstance zapisuje odniesienie do obiektu klasy GameInstance
     * @param instance odniesienie do obiektu klasy GameInstance
     */
    void setCurrentGameInstance(GameInstance &instance);
    /**
     * @brief printScoreBoard wyświetla tabele wyników
     */
    void printScoreBoard();
    /**
     * @brief deleteScoreBoard kasuje tabele wyników
     */
    void deleteScoreBoard();
    /**
     * @brief destruktor
     */
    ~MainWindow();


private slots:
    /**
     * @brief on_startButton_released funkcja odpowiedziala na rozpoczęcie rozgrywki generuje
     * pola planszy przypisuje im fukcje oraz ikony wpływa dodatkowo na logikę związaną z UI
     */
    void on_startButton_released();
    /**
     * @brief on_resetButton_clicked resetuje aktualną rozgrywkę niszcząc planszę i resetując liczniki
     */
    void on_resetButton_clicked();
    /**
     * @brief changeIcon funkcja odpowiedzialna za odczytanie ruchu gracza i jeśli jest to ruch poprwany wywołanie logiki zmiany ikon oraz
     * położenia obiektów typu tile w tabeli w obiekcie GameMode
     * @param _x położenie pola w osi X
     * @param _y położenie pola w osi Y
     */
    void changeIcon(int _x, int _y);
    /**
     * @brief updateTimer odświerza wartości liczników w trakcie gry i w odpowiednich przypadkach sprawdzanie win conditions
     */
    void updateTimer();
    /**
     * @brief winScreen funckja odpowiedzialna za wyświetlanie ekranu zwycięstwa i wywołanie związanej z wygraną logiki
     */
    void winScreen();
    /**
     * @brief loseScreen funkcja odpoweidzialna za wyświetlenie ekranu przegranej i wywołanie związanej z wygraną logiki
     */
    void loseScreen();
    /**
     * @brief on_filePickerActivationButton_clicked fukcja odpowiedzialna za wyświetlanie okna wczytywania obrazów
     */
    void on_filePickerActivationButton_clicked();

private:
    Ui::MainWindow *ui;
    /**
     * @brief currentGameInstance odniesienie do obiektu typu GameInstance
     */
    GameInstance* currentGameInstance;
    /**
     * @brief puzzleButtons tabela przycisków z których składa się plansza gry
     */
    QVector<QVector<QPushButton*>> puzzleButtons;
    /**
     * @brief timer obiekt typu timer
     */
    QTimer* timer = new QTimer(this);
    /**
     * @brief timerValue początkowa wartość timera
     */
    int timerValue=0;
    /**
     * @brief currentNumberOfTiles zmienna odpowiedzialna za przechowywanie aktualnej ilości pól na planszy w jednej kolumnie
     */
    int currentNumberOfTiles;
    /**
     * @brief currentPhotoFile zmienna przechowująca aktualnie wybrany obrazek
     */
    QString currentPhotoFile;
    /**
     * @brief currentScore zmienna przechowująca aktualny wynik
     */
    int currentScore;
};
#endif // MAINWINDOW_H
