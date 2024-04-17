#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamemode.h"
#include "tile.h"
#include "QGridLayout"
#include "QTimer"
#include "QLabel"
#include "QFileDialog"
#include "QMessageBox"


/**
 * @brief MainWindow::MainWindow konstruktor
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::on_startButton_released);

}
/**
 * @brief MainWindow::~MainWindow destruktor
 */
MainWindow::~MainWindow()
{

    delete ui;
}
/**
 * @brief MainWindow::setCurrentGameInstance zapisuje odniesienie do obiektu klasy GameInstance
 * @param instance odniesienie do obiektu klasy GameInstance
 */
void MainWindow::setCurrentGameInstance(GameInstance &instance){
    this->currentGameInstance = &instance;
    connect(timer, &QTimer::timeout, this, [=](){
        updateTimer();
    });
    printScoreBoard();
};
/**
 * @brief MainWindow::on_startButton_released funkcja odpowiedziala na rozpoczęcie rozgrywki generuje
 * pola planszy przypisuje im fukcje oraz ikony wpływa dodatkowo na logikę związaną z UI
 */
void MainWindow::on_startButton_released()
{
    ui->winLoseLabel->setText("");
    int gameModeType;
    if(ui->winCheckBox->isChecked())
        gameModeType=1;
    else
        gameModeType=0;
    ui->winCheckBox->setEnabled(false);
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
            });

        }
        layout->addLayout(rowLayout);
    }
    ui->frameForButtons->setLayout(layout);
    ui->pushButton->setEnabled(false);
    ui->resetButton->setEnabled(true);
    timer->start(1000);
}
/**
 * @brief MainWindow::on_resetButton_clicked resetuje aktualną rozgrywkę niszcząc planszę i resetując liczniki
 */
void MainWindow::on_resetButton_clicked()
{
    QLayout* layout = ui->frameForButtons->layout();

    qDeleteAll(ui->frameForButtons->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete layout;
    timer->stop();
    timerValue=0;
    ui->timerLabel->setText(QString::number(timerValue));
    currentScore=0;
    ui->currentScoreLabel->setText(QString::number(currentScore));
    currentGameInstance->deleteGameMode();
        ui->winCheckBox->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->resetButton->setEnabled(false);
}
/**
 * @brief MainWindow::changeIcon funkcja odpowiedzialna za odczytanie ruchu gracza i jeśli jest to ruch poprwany wywołanie logiki zmiany ikon oraz
 * położenia obiektów typu tile w tabeli w obiekcie GameMode
 * @param _x położenie pola w osi X
 * @param _y położenie pola w osi Y
 */
void MainWindow::changeIcon(int _x, int _y){
    bool check = currentGameInstance->currentGameMode->passPushCheck(_x,_y);
    if(check){
        int currentWorkedOnXCordStarting;
        int currentWorkedOnYCordStarting;
        int futureEmptyXCord;
        int futureEmptyYCord;
        int currentEmptyXCord;
        int currentEmptyYCord;
        QList<int> workingList = currentGameInstance->currentGameMode->getNewImageCords();
        currentWorkedOnXCordStarting=workingList.at(0);
        currentWorkedOnYCordStarting=workingList.at(1);
        futureEmptyXCord=workingList.at(2);
        futureEmptyYCord=workingList.at(3);
        currentEmptyXCord=workingList.at(4);
        currentEmptyYCord=workingList.at(5);
        QPushButton* currentButton = puzzleButtons[_x][_y];
        currentButton->setIcon(currentGameInstance->currentGameMode->buttonIcons[currentWorkedOnXCordStarting][currentWorkedOnYCordStarting]);
        QPushButton* emptyButton = puzzleButtons[currentEmptyXCord][currentEmptyYCord];
        emptyButton->setIcon(currentGameInstance->currentGameMode->buttonIcons[futureEmptyXCord][futureEmptyYCord]);
        currentGameInstance->currentGameMode->switchTiles(_x,_y,currentEmptyXCord,currentEmptyYCord);
        if(currentGameInstance->currentGameMode->checkWinCondition()){

            timer->stop();
            winScreen();
        }
        else{

        }
    }
}
/**
 * @brief MainWindow::updateTimer odświerza wartości liczników w trakcie gry i w odpowiednich przypadkach sprawdzanie win conditions
 */
void MainWindow::updateTimer(){
    timerValue++;
    ui->timerLabel->setText(QString::number(timerValue));
    if(ui->winCheckBox->isChecked()){
        if(auto timedGameModeDownCast = dynamic_cast<TimedGameMode*>(currentGameInstance->currentGameMode)){
            currentScore=timedGameModeDownCast->currentScore(timerValue);
            ui->currentScoreLabel->setText(QString::number(currentScore));
        }
    }
    if(ui->winCheckBox->isChecked()&&currentGameInstance->currentGameMode->timeCheck(timerValue)){
        timer->stop();
        loseScreen();

    }
}
/**
 * @brief MainWindow::winScreen funckja odpowiedzialna za wyświetlanie ekranu zwycięstwa i wywołanie związanej z wygraną logiki
 */
void MainWindow::winScreen(){
    for(int i=0;i<currentNumberOfTiles;i++){
        for(int j=0;j<currentNumberOfTiles;j++){
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode->originalIcons[i][j]);
            puzzleButtons[i][j]->blockSignals(true);

        }
    }
    ui->winLoseLabel->setText("Won");
    ui->winCheckBox->setEnabled(true);
    if(ui->winCheckBox->isChecked()){
        bool inTopFive = currentGameInstance->currentScoreBoard->updateScores(currentScore);
        if(inTopFive){
            currentGameInstance->currentScoreBoard->writeScores();
            deleteScoreBoard();
            printScoreBoard();
        }
    }
}
/**
 * @brief MainWindow::loseScreen funkcja odpoweidzialna za wyświetlenie ekranu przegranej i wywołanie związanej z wygraną logiki
 */
void MainWindow::loseScreen(){
    for(int i=0;i<currentNumberOfTiles;i++){
        for(int j=0;j<currentNumberOfTiles;j++){
            puzzleButtons[i][j]->setIcon(currentGameInstance->currentGameMode->originalIcons[i][j]);
            puzzleButtons[i][j]->blockSignals(true);
            ui->winLoseLabel->setText("Lost");
        }
    }
            ui->winCheckBox->setEnabled(true);
}
/**
 * @brief MainWindow::on_filePickerActivationButton_clicked fukcja odpowiedzialna za wyświetlanie okna wczytywania obrazów
 */
void MainWindow::on_filePickerActivationButton_clicked()
{
    QString ostatniObraz;
    if(!currentPhotoFile.isEmpty()){
        ostatniObraz = currentPhotoFile;
    }

    currentPhotoFile = QFileDialog::getOpenFileName(this, tr("Open Image"),"",tr("ImageFiles(*.png)"));
    if(!currentPhotoFile.isEmpty()){
        ui->pushButton->setEnabled(true);

    }
    else if(!ostatniObraz.isEmpty()){
        currentPhotoFile = ostatniObraz;

    }
}
/**
 * @brief MainWindow::printScoreBoard wyświetla tabele wyników
 */
void MainWindow::printScoreBoard(){
    QVBoxLayout* layout = new QVBoxLayout(ui->scoreBoardFrame);
    for(int i=0;i<currentGameInstance->currentScoreBoard->getScoreListSize();i++){
        QLabel *label = new QLabel(QString::number(currentGameInstance->currentScoreBoard->getScore(i)));
        layout->addWidget(label);
    }
    ui->scoreBoardFrame->setLayout(layout);
}
/**
 * @brief MainWindow::deleteScoreBoard kasuje tabele wyników
 */
void MainWindow::deleteScoreBoard(){
    QLayout* layout = ui->scoreBoardFrame->layout();

    qDeleteAll(ui->scoreBoardFrame->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete layout;
}
