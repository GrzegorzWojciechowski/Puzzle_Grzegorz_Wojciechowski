#ifndef PUZZLEBUTTON_H
#define PUZZLEBUTTON_H

#include "qpushbutton.h"
#include <QWidget>

class PuzzleButton : public QPushButton
{
    Q_OBJECT
public:
    PuzzleButton(QWidget *parent = nullptr): QPushButton(parent){};

    PuzzleButton(QString);
    void passIndex(int i, int j){

    }
    void setIndex(int i, int j){

    }
private:
    int index_i;
    int index_j;

signals:


};



#endif // PUZZLEBUTTON_H
