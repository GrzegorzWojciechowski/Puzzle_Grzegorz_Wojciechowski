#include "scoreboard.h"
#include "QFile"
#include "QTextStream"

/**
 * @brief ScoreBoard::ScoreBoard konsrtruktor klasy ScoarBoard
 */

ScoreBoard::ScoreBoard() {}

/**
 * @brief ScoreBoard::readScores wczytuje wyniki z pliku
 */

void ScoreBoard::readScores(){
    QFile file("scores.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
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

/**
 * @brief ScoreBoard::writeScores funkcja odpowiedzialna za zapisywanie listy akualnych wyników do pliku
 */

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

/**
 * @brief ScoreBoard::updateScores funkcja odpowiedzialna za sprawdzanie czy nowy wynik znajduje się w top 5 wyników wywołuje również funkcję
 * zapisu nowych wyników do pliku
 * @param newScore nowy wynik
 * @return bool true jeśli wynik znajduje się w top 5 false jeśli nie
 */

bool ScoreBoard::updateScores(int newScore){
    if(newScore<=scores.back()||scores.empty()){
        return false;
    }
    else{
        scores.append(newScore);
        std::sort(scores.begin(), scores.end(), [](const int& a, const int& b) {
            return a > b;
        });
        if (scores.size() > 5) {
            scores.erase(scores.begin() + 5, scores.end());
        }
        writeScores();
        return true;
    }
};

/**
 * @brief ScoreBoard::getScoreListSize zwraca rozmiar tablicy wyników, funkcja niestety nie ma konkretnego zastosowania
 * w aplikacji z powodu wybranego sposoby wczytywania wyników, zostawiona w celu udokumentowania procesu myślowego
 * lub w przypadku późniejszego przebudowywania aplikacji
 * @return rozmiar tablicy wyników
 */

int ScoreBoard::getScoreListSize(){
    return scores.size();
};

/**
 * @brief ScoreBoard::getScore zwraca wynik znajdujący się na określonej pozycji listy wyników
 * @param scorePlace miejsce w liście wynikow
 * @return wynik
 */

int ScoreBoard::getScore(int scorePlace){
    if(scorePlace<scores.size()){
        return scores.at(scorePlace);
    }
};

