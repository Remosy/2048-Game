#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QPoint>
#include <QPropertyAnimation>
class Cell : public QLabel
{
    Q_OBJECT
public:
    int cell_val;
    bool hasDone;  //Mark a cell has been combined with another cell, Defult: false
    QPropertyAnimation *animation;

    explicit Cell(int val);
    void updateCell(int val){cell_val = val;}
    int getCell(){return cell_val;}
    void drawCell();
    void moveAnime(QRect pos1, QRect pos2);



signals:

public slots:
};

#endif // CELL_H
