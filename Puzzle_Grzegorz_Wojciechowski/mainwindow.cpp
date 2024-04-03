#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamemode.h"
#include "tile.h"
#include "QGridLayout"
#include "QTimer"
#include "QLabel"
#include "QFileDialog"
#include "QMessageBox"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->filePickerActivationButton, &QPushButton::clicked, this, &MainWindow::on_filePickerActivationButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentGameInstance(GameInstance &instance){
    this->currentGameInstance = &instance;
    connect(timer, &QTimer::timeout, this, [=](){
        updateTimer();
    });
};



void MainWindow::on_pushButton_released()
{
    ui->winLoseLabel->setText("");
    int gameModeType;
    if(ui->winCheckBox->isChecked())
        gameModeType=1;
    else
        gameModeType=0;
    currentNumberOfTiles = ui->numberOfTiles->value();;
    int buttonSize = 512/currentNumberOfTiles;
    QSize iconSize(buttonSize-4, buttonSize-4);
    int diff = ui->horizontalSlider->value();
    currentGameInstance->gameStartFunction(currentNumberOfTiles,currentPhotoFile,gameModeType,diff);
    currentGameInstance->currentGameMode->mixTheTiles();
    if(gameModeType==1){
        if(auto timedGameModeDownCast = dynamic_cast<TimedGameMode*>(currentGameInstance->currentGameMode)){
            ui->maxTime->setText(QString::number(timedGameModeDownCast->getMaxTime()));
        }
    }
    else{
        ui->maxTime->setText("__");
    }


    puzzleButtons.resize(currentNumberOfTiles);
    QVBoxLayout* layout = new QVBoxLayout(ui->frameForButtons);
    for (int i = 0; i < currentNumberOfTiles; ++i) {
        puzzleButtons[i].resize(currentNumberOfTiles);
        QHBoxLayout* rowLayout = new QHBoxLayout();
        for (int j = 0; j < currentNumberOfTiles; ++j) {
            puzzleButtons[i][j] = new QPushButton();
            puzzleButtons[i][j]->setFixedSize(buttonSize, buttonSize);
            rowLayout->addWidget(puzzleButtons[i][j]);
            int x = currentGameInstance->currentGameMode->puzzleTiles[i][j].getStartingXIndex();
            int y = currentGameInstance->currentGameMode->puzzleTiles[i][j].getStartingYIndex();
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode->buttonIcons[x][y]);
            puzzleButtons[i][j]->setIconSize(iconSize);
            connect(puzzleButtons[i][j], &QPushButton::clicked, this, [=](){
                changeIcon(i,j);
                //puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode.buttonIcons[1][1]);
                //puzzleButtons[i][j]->setIconSize(iconSize);
            });

        }
        layout->addLayout(rowLayout);
    }
    ui->frameForButtons->setLayout(layout);
    timer->start(1000);
}

void MainWindow::on_resetButton_clicked()
{
    QLayout* layout = ui->frameForButtons->layout();

    qDeleteAll(ui->frameForButtons->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete layout;
    ui->testSpinBox->setValue(0);
    timer->stop();
    timerValue=0;
    ui->timerLabel->setText(QString::number(timerValue));
}

void MainWindow::changeIcon(int _x, int _y){
    bool check = currentGameInstance->currentGameMode->passPushCheck(_x,_y);
    if(check){
        int a;
        int b;
        int c;
        int d;
        int _h;
        int _g;
        currentGameInstance->currentGameMode->getNewImageCords(a,b,c,d,_h,_g);
        QPushButton* currentButton = puzzleButtons[_x][_y];
        currentButton->setIcon(currentGameInstance->currentGameMode->buttonIcons[a][b]);
        QPushButton* emptyButton = puzzleButtons[_h][_g];
        emptyButton->setIcon(currentGameInstance->currentGameMode->buttonIcons[c][d]);
        currentGameInstance->currentGameMode->switchTiles(_x,_y,_h,_g);
        if(currentGameInstance->currentGameMode->checkWinCondition()){
            //ui->testSpinBox->setValue(1);
            timer->stop();
            winScreen();
        }
        else{
           ui->testSpinBox->setValue(2);
        }
    //puzzleButton[i]->setIcon(currentGameInstance->currentGameMode.buttonIcons[a][b]);
    }
}

void MainWindow::updateTimer(){
    timerValue++;
    ui->timerLabel->setText(QString::number(timerValue));
    if(ui->winCheckBox->isChecked()&&currentGameInstance->currentGameMode->timeCheck(timerValue)){
        //ui->testSpinBox->setValue(3);
        timer->stop();
        loseScreen();

    }
}

void MainWindow::winScreen(){
    for(int i=0;i<currentNumberOfTiles;i++){
        for(int j=0;j<currentNumberOfTiles;j++){
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode->originalIcons[i][j]);
            //disconnect(puzzleButtons[i][j], &QPushButton::clicked, this);
            puzzleButtons[i][j]->blockSignals(true);
            ui->winLoseLabel->setText("Won");
        }
    }
}
void MainWindow::loseScreen(){
    for(int i=0;i<currentNumberOfTiles;i++){
        for(int j=0;j<currentNumberOfTiles;j++){
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode->originalIcons[i][j]);
            //disconnect(puzzleButtons[i][j], &QPushButton::clicked, this);
            puzzleButtons[i][j]->blockSignals(true);
            ui->winLoseLabel->setText("Lost");
        }
    }
}


void MainWindow::on_filePickerActivationButton_clicked()
{
    QString ostatniObraz;
    if(!currentPhotoFile.isEmpty()){
        ostatniObraz = currentPhotoFile;
    }
    disconnect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_pushButton_released);
    disconnect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
    currentPhotoFile = QFileDialog::getOpenFileName(this, tr("Open Image"),"",tr("ImageFiles(*.png)"));
    if(!currentPhotoFile.isEmpty()){
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_pushButton_released);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
    }
    else if(!ostatniObraz.isEmpty()){
        currentPhotoFile = ostatniObraz;
        connect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_pushButton_released);
        connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
    }
}

