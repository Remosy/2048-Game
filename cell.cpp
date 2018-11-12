#include "cell.h"
#include <QGraphicsDropShadowEffect>

Cell::Cell(int val):
    QLabel()
{
    setAlignment(Qt::AlignCenter);
    cell_val = val;
    hasDone = false;
}

void Cell::moveAnime(QRect pos1, QRect pos2)
{
    animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setStartValue(pos1);
    animation->setEndValue(pos2);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void Cell::drawCell()
{
    setFixedSize(90,90);
    if (cell_val == 0) {
        setText("");
        setStyleSheet("Cell { background: rgb(204,192,179); border-radius: 3px; }");
    } else {
        setText(QString::number(getCell()));
        switch (getCell()) {
        case 2: {
            setStyleSheet("Cell { background: rgb(238,228,218); color: rgb(119,110,101); font: 85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 4: {
            setStyleSheet("Cell { background: rgb(237,224,200); color: rgb(119,110,101); font: 85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 8: {
            setStyleSheet("Cell { background: rgb(242,177,121); color: rgb(255,255,255); font:  85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 16: {
            setStyleSheet("Cell { background: rgb(245,150,100); color: rgb(255,255,255); font:  85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 32: {
            setStyleSheet("Cell { background: rgb(245,125,95); color: rgb(255,255,255); font:  85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 64: {
            setStyleSheet("Cell { background: rgb(245,95,60); color: rgb(255,255,255); font:  85 55pt 'Arial Black'; border-radius: 3px; }");
            break;
        }
        case 128: {
            setStyleSheet("Cell { background: rgb(237,207,114); color: rgb(255,255,255); font:  85 45pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 256: {
            setStyleSheet("Cell { background: rgb(237,204,97); color: rgb(255,255,255); font:  85 45pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        case 512: {
            setStyleSheet("Cell { background: rgb(237,204,97); color: rgb(255,255,255); font:  85 45pt 'Arial Black'; border-radius: 3px; }");
            break;
        }
        case 1024: {
            setStyleSheet("Cell { background: rgb(237,204,97); color: rgb(255,255,255); font:  85 35pt 'Arial Black'; border-radius: 3px; }");
            break;
        }
        case 2048: {
            setStyleSheet("Cell { background: rgb(237,204,97); color: rgb(255,255,255); font:  85 35pt 'Arial Black'; border-radius: 3px; }");
            break;
        }
        default: {
            setStyleSheet("Cell { background: rgb(238,228,218); color: rgb(119,110,101); font:  85 55pt 'Arial Black'; border-radius: 3px;}");
            break;
        }
        }
    }
}
