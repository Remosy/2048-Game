#ifndef BOARDGUI_H
#define BOARDGUI_H
#include "board.h"
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QKeyEvent>

class BoardGUI : public QWidget
{
    Q_OBJECT
public:
    explicit BoardGUI(QWidget *parent = 0);

private:
    Board  *the_board;
    Board  *fake_board;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *button_restart;
    QPushButton *button_aiSolver;
    QWidget *board;
    QWidget *fakeBoard;
    QGridLayout *boardLayout;
    QGridLayout *boardBackground;

    void initBoardUI();

private slots:
    void drawBoardUI();
    void restartGame();

protected:
    void keyPressEvent(QKeyEvent *event);


};

#endif // BOARDGUI_H
