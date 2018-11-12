#include "boardgui.h"


using namespace std;
BoardGUI::BoardGUI(QWidget *w) : QWidget(w)
{
    //QWidget *w = new QWidget;
    setWindowOpacity(0.90);
    setFixedSize(470,610);

    QFont labelFont("Arial",24, QFont::Bold, false);
    QFont labelFont2("Arial",16, QFont::Bold, false);

    label_1 = new QLabel(this);
    label_1->setText("2048");
    label_1->setAlignment(Qt::AlignCenter);
    label_1->setGeometry(10,10,181,75);
    label_1->setFont(labelFont);
    label_1->setStyleSheet("background-color: rgb(255, 212, 58);color: rgb(255, 255, 255);");
    label_2 = new QLabel(this);
    label_2->setText("Game");
    label_2->setAlignment(Qt::AlignCenter);
    label_2->setGeometry(10,60,181,61);
    label_2->setFont(labelFont);
    label_2->setStyleSheet("background-color: rgb(255, 212, 58);color: rgb(255, 255, 255);");


    label_3 = new QLabel(this);
    label_3->setText("Score");
    label_3->setAlignment(Qt::AlignCenter);
    label_3->setGeometry(210,10,119,35);
    label_3->setFont(labelFont2);
    label_3->setStyleSheet("background-color: rgb(217, 196, 158);color: rgb(255, 255, 255);");
    label_4 = new QLabel(this);
    label_4->setAlignment(Qt::AlignCenter);
    label_4->setGeometry(210,40,119,31);
    label_4->setFont(labelFont);
    label_4->setStyleSheet("background-color: rgb(217, 196, 158);color: rgb(255, 255, 255);");

    /*label_5 = new QLabel(this);
    label_5->setText("Highest Score");
    label_5->setAlignment(Qt::AlignCenter);
    label_5->setGeometry(340,10,119,35);
    label_5->setFont(labelFont2);
    label_5->setStyleSheet("background-color: rgb(217, 196, 158);color: rgb(255, 255, 255);");
    label_6 = new QLabel(this);
    label_6->setAlignment(Qt::AlignCenter);
    label_6->setGeometry(340,40,119,31);
    label_6->setFont(labelFont);
    label_6->setStyleSheet("background-color: rgb(217, 196, 158);color: rgb(255, 255, 255);");*/

    button_restart = new QPushButton(this);
    button_restart->setText("Restart");
    button_restart->setGeometry(220,80,91,41);
    button_restart->setFont(labelFont2);
    button_restart->setStyleSheet("background-color: rgb(253, 128, 8); border-radius: 3px; color: rgb(255, 255, 255);");
    connect(button_restart, SIGNAL (released()), this, SLOT (restartGame()));

    /*button_aiSolver = new QPushButton(this);
    button_aiSolver->setText("AI Solver");
    button_aiSolver->setGeometry(360,80,81,41);
    button_aiSolver->setFont(labelFont2);
    button_aiSolver->setStyleSheet("background-color: rgb(253, 128, 8); border-radius: 3px; color: rgb(255, 255, 255);");*/

   fakeBoard = new QWidget(this);
   fakeBoard->setGeometry(25,150,420,420);
   fakeBoard->setStyleSheet("background-color: rgb(185, 173, 162);");
   boardBackground = new QGridLayout;
   fakeBoard->setLayout(boardBackground);
   fake_board = new Board();
    for(int ii = 0; ii < 4; ii++){
        for(int jj = 0; jj < 4; jj++){
             boardBackground->addWidget(fake_board->theBoard[ii][jj],ii, jj,Qt::AlignCenter);
             fake_board->theBoard[ii][jj]->drawCell();
        }
    }

    board = new QWidget(this);
    board->setGeometry(25,150,420,420);
    //board->setStyleSheet("background-color: rgb(185, 173, 162);");
    boardLayout = new QGridLayout;
    board->setLayout(boardLayout);
    initBoardUI();
    this->setFocusPolicy(Qt::StrongFocus);
}

void BoardGUI::restartGame()
{
    cout<<"Restart Game"<<endl;
    initBoardUI();
}


void BoardGUI::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_Up:
        cout<<"Move: UP"<<endl;
        the_board->moveUpLeft(0);
        break;
    case Qt::Key_Down:
        cout<<"Move: DOWN"<<endl;
        the_board->moveDownRight(0);
        break;
    case Qt::Key_Left:
        cout<<"Move: LEFT"<<endl;
        the_board->moveUpLeft(1);
        break;
    case Qt::Key_Right:
        cout<<"Move: RIGHT"<<endl;
        the_board->moveDownRight(1);
        break;
    }

   //Genarate new Cell and Update Board after at least one cell has been moved
   if(the_board->hasMoved==true){
        the_board->generateNewCell();
        drawBoardUI();
        QTimer *timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(drawBoardUI()));
        timer->start(2000);
   }

   //Check GameOver
   if(the_board->checkGameEnd()==true){
       cout<<"Game Over"<< endl;
   }

   label_4->setText(QString(" %1").arg(the_board->getScore()));
   //label_6->setText(QString(" %1").arg(the_board->getMaxScore()));
}


void BoardGUI::drawBoardUI()
{

    for(int ii = 0; ii < 4; ii++){
        for(int jj = 0; jj < 4; jj++){
             boardLayout->addWidget(the_board->theBoard[ii][jj],ii, jj,Qt::AlignCenter);
             the_board->theBoard[ii][jj]->drawCell();
        }
    }
}

void BoardGUI::initBoardUI(){
    the_board = new Board();
    the_board->initBoard();
    for(int ii = 0; ii < 4; ii++){
        for(int jj = 0; jj < 4; jj++){
             boardLayout->addWidget(the_board->theBoard[ii][jj],ii, jj,Qt::AlignCenter);
             the_board->theBoard[ii][jj]->drawCell();
        }
    }
    QString score = "";
    QString maxscore = "";
    score.setNum(the_board->score);
    maxscore.setNum(the_board->maxscore);
    label_4->setText(score);
    //label_6->setText(maxscore);
}

