#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamemode.h"
#include "tile.h"
#include "QGridLayout"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_pushButton_released);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentGameInstance(GameInstance &instance){
    this->currentGameInstance = &instance;
};



void MainWindow::on_pushButton_released()
{
    int N = ui->numberOfTiles->value();;
    int buttonSize = 512/N;
    QSize iconSize(buttonSize-4, buttonSize-4);
    currentGameInstance->gameStartFunction(N,"C:/Users/grzeg/Documents/Qt_C-/test.png");
    //QPushButton* puzzleButtons[N][N];
    puzzleButtons.resize(N);
    QVBoxLayout* layout = new QVBoxLayout(ui->frameForButtons);
    for (int i = 0; i < N; ++i) {
        puzzleButtons[i].resize(N);
        QHBoxLayout* rowLayout = new QHBoxLayout();
        for (int j = 0; j < N; ++j) {
            puzzleButtons[i][j] = new QPushButton();
            puzzleButtons[i][j]->setFixedSize(buttonSize, buttonSize);
            rowLayout->addWidget(puzzleButtons[i][j]);
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode.buttonIcons[i][j]);
            puzzleButtons[i][j]->setIconSize(iconSize);
            connect(puzzleButtons[i][j], &QPushButton::clicked, this, [=](){
                changeIcon(i,j);
                //puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode.buttonIcons[1][1]);
                //puzzleButtons[i][j]->setIconSize(iconSize);
            });
            // QPushButton* button = new QPushButton();
            // button->setFixedSize(buttonSize, buttonSize);
            // rowLayout->addWidget(button);
            // button->setIcon(currentGameInstance->currentGameMode.buttonIcons[i][j]);
            // button->setIconSize(iconSize);
            // connect(button, &QPushButton::clicked, this, [=](){
            //     changeIcon(button,i,j);
            // });
        }
        layout->addLayout(rowLayout);
    }
    ui->frameForButtons->setLayout(layout);
}

void MainWindow::on_resetButton_clicked()
{
    QLayout* layout = ui->frameForButtons->layout();

    qDeleteAll(ui->frameForButtons->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete layout;
    ui->testSpinBox->setValue(0);
}

void MainWindow::changeIcon(int _x, int _y){
    bool check = currentGameInstance->currentGameMode.passPushCheck(_x,_y);
    if(check){
        int a;
        int b;
        int c;
        int d;
        int _h;
        int _g;
        currentGameInstance->currentGameMode.getNewImageCords(a,b,c,d,_h,_g);
        QPushButton* currentButton = puzzleButtons[_x][_y];
        currentButton->setIcon(currentGameInstance->currentGameMode.buttonIcons[a][b]);
        QPushButton* emptyButton = puzzleButtons[_h][_g];
        emptyButton->setIcon(currentGameInstance->currentGameMode.buttonIcons[c][d]);
        currentGameInstance->currentGameMode.switchTiles(_x,_y,_h,_g);
        if(currentGameInstance->currentGameMode.checkWinCondition()){
            ui->testSpinBox->setValue(1);
        }
        else{
           ui->testSpinBox->setValue(2);
        }
    //puzzleButton[i]->setIcon(currentGameInstance->currentGameMode.buttonIcons[a][b]);
    }
}

