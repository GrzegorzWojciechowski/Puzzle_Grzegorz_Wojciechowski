#include "scoreboard.h"
#include "QFile"
#include "QTextStream"
ScoreBoard::ScoreBoard() {}

void ScoreBoard::readScores(){
    QFile file("scores.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            //int line = in.readLine();
            int line;
            in >> line;
            scores.append(line);

        }
        if(scores.size()<5){
            while(scores.size()<5)
                scores.append(0);
        }
        file.close();
    }
    else{
        if(file.open(QIODevice::WriteOnly)){

        }
    }
};

void ScoreBoard::writeScores(){
    QFile file("scores.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const int& score : scores) {
            out << score << "\n";
        }
        file.close();
    }
};

bool ScoreBoard::updateScores(int newScore){
    if(newScore<=scores.back()||scores.empty()){
        return false;
    }
    else{
        scores.append(newScore);
        std::sort(scores.begin(), scores.end(), [](const int& a, const int& b) {
            return a > b; // Sort in descending order
        });
        if (scores.size() > 5) {
            scores.erase(scores.begin() + 5, scores.end()); // Keep only top 5 scores
        }
        writeScores();
        return true;
    }
};

int ScoreBoard::getScoreListSize(){
    return scores.size();
};

int ScoreBoard::getScore(int scorePlace){
    if(scorePlace<scores.size()){
        return scores.at(scorePlace);
    }
};

