#include "mainwindow.h"
#include "gamemode.h"
#include "tile.h"
#include "gameinstance.h"
#include <QApplication>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameInstance currentGameInstance;
    MainWindow w;
    w.setCurrentGameInstance(currentGameInstance);
    w.show();

    return a.exec();
}
