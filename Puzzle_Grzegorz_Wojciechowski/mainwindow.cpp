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




void MainWindow::on_pushButton_released()
{
    int N = 5;
    int buttonSize = 60;
    QPushButton* puzzleButtons[N][N];

    QVBoxLayout* layout = new QVBoxLayout(ui->frameForButtons);
    for (int i = 0; i < N; ++i) {
        QHBoxLayout* rowLayout = new QHBoxLayout();
        for (int j = 0; j < N; ++j) {
            puzzleButtons[i][j] = new QPushButton(QString("Button %1").arg(i * N + j));
            puzzleButtons[i][j]->setFixedSize(buttonSize, buttonSize);
            rowLayout->addWidget(puzzleButtons[i][j]);

            connect(puzzleButtons[i][j], &QPushButton::clicked, this, [=](){
                int cV = ui->numberOfTiles->value();
                ui->numberOfTiles->setValue((cV+i * N + j));
            });
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
}

