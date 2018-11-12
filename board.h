#ifndef BOARD_H
#define BOARD_H
#include <cell.h>
#include <iostream>
#include <QLabel>
#include <vector>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QParallelAnimationGroup>
using namespace std;

class Board
{
public:
    Cell *theBoard[4][4];
//QParallelAnimationGroup *qParallelAnimationGroup;
    vector<Cell*> preserveCells;
    vector<Cell*> animationGroup;
    bool hasMoved;
    int score;
    int maxscore;
    Board();

    //ENVIRONMENT
    void initBoard(); //Restart game with 2 new random numbers
    void updateBoard();
    void deleteBoard();

    //ACTION
    void move(int direction1, int direction2);//Direction 1->UP:0 DOWN:1 LEFT:0 RIGHT:1    Direction 2-><Vertical:0   Horizontal:1>
    void moveUpLeft(int type);
    void moveDownRight(int type);
    void generateNewCell();
    bool hasFailed();
    void combine2Cells(Cell *master_cell, Cell *minor_cell);
    void restorePreservers();
    void restoreAnimations();

    bool checkGameEnd();

    //Score
    int getScore() const { return score; }
    int getMaxScore() const { return maxscore; }

};

#endif // BOARD_H
