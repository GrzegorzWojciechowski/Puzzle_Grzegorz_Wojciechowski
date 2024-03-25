#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameinstance.h"
#include "qpushbutton.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setCurrentGameInstance(GameInstance &instance);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_numberOfTiles_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_released();

    void on_resetButton_clicked();

    void changeIcon(int _x, int _y);

private:
    Ui::MainWindow *ui;
    GameInstance* currentGameInstance;
    QVector<QVector<QPushButton*>> puzzleButtons;
};
#endif // MAINWINDOW_H
