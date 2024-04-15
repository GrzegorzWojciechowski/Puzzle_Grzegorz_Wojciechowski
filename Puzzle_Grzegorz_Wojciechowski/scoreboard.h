#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "QList"
class ScoreBoard
{
public:
    ScoreBoard();

    void writeScores();
    bool updateScores(int newScore);
    void readScores();
    int getScoreListSize();
    int getScore(int scorePlace);
private:
    QList<int> scores;

};

#endif // SCOREBOARD_H
