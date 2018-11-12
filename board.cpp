#include "board.h"
#include "cell.h"
#include <iostream>

using namespace std;
static int choice[] = {2,4};

Board::Board()
{
    for(int ii = 0; ii <= 3; ii++){
        for(int jj = 0; jj <= 3; jj++){
            theBoard[ii][jj] = new Cell(0);
        }
    }
    score = 0;
    maxscore = 0;
}

bool Board::hasFailed()
{
return true;
}

void Board::generateNewCell()
{
    int x = 0;
    int y = 0;
    bool hasFound = false;
    while(hasFound==false){
        x = rand()%4;
        y = rand()%4;
       if(theBoard[x][y]->cell_val==0){
           theBoard[x][y]->cell_val = (rand()%10+1) < 9? choice[0]:choice[1];
           cout<<"New Cell ="<< x << "," << y<<" =>" << theBoard[x][y]->cell_val << endl;
           hasFound = true;
       }
    }
}

void Board::restorePreservers()
{
    while(!preserveCells.empty()){
        preserveCells.back()->hasDone = false;
        preserveCells.pop_back();
    }
}

void Board::restoreAnimations()
{
    while(!animationGroup.empty()){
        animationGroup.back()->animation->stop();
        animationGroup.pop_back();
    }
}



void Board::combine2Cells(Cell *master_cell, Cell *minor_cell)
{
     master_cell->cell_val = master_cell->cell_val + minor_cell->cell_val;
     score+=master_cell->cell_val;
     cout<<"score: "<<score<<endl;
     preserveCells.push_back(master_cell);
     master_cell->hasDone = true;
     minor_cell->cell_val = 0;
     master_cell->drawCell();
     minor_cell->drawCell();
}

/*
 * UP:(Type)0(Key)0 LEFT: (Type)1(Key)0
 */
void Board::moveUpLeft(int type){
    //refresh public variables
    restorePreservers();
    hasMoved = false;
    for(int ii = 0; ii <= 3; ii++){
        int pos_key = -1;
        for(int jj = 0; jj <= 3; jj++){
            if(type==0){//MOVE UP
                //cout<<jj<<","<<jj<<" = "<<theBoard[jj][ii]->cell_val<<endl;
                if(theBoard[jj][ii]->cell_val!=0){
                    if(theBoard[pos_key+1][ii]->cell_val!=theBoard[jj][ii]->cell_val || theBoard[pos_key+1][ii]->cell_val==0){
                        //theBoard[jj][ii]->moveAnime(theBoard[jj][ii]->geometry(),theBoard[pos_key+1][ii]->geometry());
                        theBoard[pos_key+1][ii]->cell_val=theBoard[jj][ii]->cell_val;
                        theBoard[jj][ii]->cell_val=0;
                        hasMoved = true;

                    }

                    if(pos_key > -1 && theBoard[pos_key+1][ii]->cell_val==theBoard[pos_key][ii]->cell_val
                            && theBoard[pos_key][ii]->hasDone==false){
                        cout<< "POSKey+1 = " << pos_key+1<<","<<ii<<"=>"<< theBoard[pos_key+1][ii]->cell_val <<endl;
                        cout<< " POSKey = " << pos_key<<","<<ii<<"=>"<< theBoard[pos_key][ii]->cell_val<< endl;
                        //theBoard[pos_key+1][ii]->moveAnime(theBoard[pos_key+1][ii]->geometry(),theBoard[pos_key][ii]->geometry());
                        combine2Cells(theBoard[pos_key][ii],theBoard[pos_key+1][ii]);
                        hasMoved = true;
                        pos_key--;
                    }
                    pos_key = pos_key+1;
                }
            }else{//MOVE LEFT
                if(theBoard[ii][jj]->cell_val!=0){
                    if(theBoard[ii][pos_key+1]->cell_val!=theBoard[ii][jj]->cell_val || theBoard[ii][pos_key+1]->cell_val==0){
                            //theBoard[jj][ii]->moveAnime(theBoard[jj][ii]->geometry(),theBoard[ii][pos_key+1]->geometry());
                            theBoard[ii][pos_key+1]->cell_val=theBoard[ii][jj]->cell_val;
                            theBoard[ii][jj]->cell_val=0;
                            hasMoved = true;

                    }
                        if(pos_key > -1 && theBoard[ii][pos_key+1]->cell_val==theBoard[ii][pos_key]->cell_val
                                && theBoard[ii][pos_key]->hasDone==false){
                            cout<< "POSKey+1 = " << pos_key+1<<","<<ii<<"=>"<< theBoard[ii][pos_key+1]->cell_val <<endl;
                            cout<< " POSKey = " << pos_key<<","<<ii<<"=>"<< theBoard[ii][pos_key]->cell_val<< endl;
                            //theBoard[ii][pos_key+1]->moveAnime(theBoard[ii][pos_key+1]->geometry(),theBoard[ii][pos_key]->geometry());
                            combine2Cells(theBoard[ii][pos_key],theBoard[ii][pos_key+1]);
                            hasMoved = true;
                            pos_key--;
                        }
                        pos_key = pos_key+1;
                 }
            }
        }
    }
}

/*
 * DOWN:(Type)0(Key)1 RIGHT: (Type)1(Key)1
 */
void Board::moveDownRight(int type){
    //refresh public variables
    restorePreservers();
    hasMoved = false;

    for(int ii = 3; ii >= 0; ii--){
        int pos_key = 4;
        for(int jj = 3; jj >= 0; jj--){
            if(type==0){//MOVE DOWN
                if(theBoard[jj][ii]->cell_val!=0){
                    if(theBoard[pos_key-1][ii]->cell_val!=theBoard[jj][ii]->cell_val || theBoard[pos_key-1][ii]->cell_val==0){
                        //theBoard[jj][ii]->moveAnime(theBoard[jj][ii]->geometry(),theBoard[pos_key-1][ii]->geometry());
                        theBoard[pos_key-1][ii]->cell_val=theBoard[jj][ii]->cell_val;
                        theBoard[jj][ii]->cell_val=0;
                        hasMoved = true;

                    }
                    if(pos_key < 4 && theBoard[pos_key-1][ii]->cell_val==theBoard[pos_key][ii]->cell_val
                            && theBoard[pos_key][ii]->hasDone==false){
                        cout<< "POSKey-1 = " << pos_key-1<<","<<ii<<"=>"<< theBoard[pos_key-1][ii]->cell_val <<endl;
                        cout<< " POSKey = " << pos_key<<","<<ii<<"=>"<< theBoard[pos_key][ii]->cell_val<< endl;
                        combine2Cells(theBoard[pos_key][ii],theBoard[pos_key-1][ii]);
                        hasMoved = true;
                        pos_key++;
                    }
                    pos_key = pos_key-1;
                }
            }else{//MOVE RIGHT
                if(theBoard[ii][jj]->cell_val!=0){
                    if(theBoard[ii][pos_key-1]->cell_val!=theBoard[ii][jj]->cell_val || theBoard[ii][pos_key-1]->cell_val==0){
                        //theBoard[jj][ii]->moveAnime(theBoard[jj][ii]->geometry(),theBoard[ii][pos_key-1]->geometry());
                        theBoard[ii][pos_key-1]->cell_val=theBoard[ii][jj]->cell_val;
                        theBoard[ii][jj]->cell_val=0;
                        hasMoved = true;

                    }
                    if(pos_key < 4 && theBoard[ii][pos_key-1]->cell_val==theBoard[ii][pos_key]->cell_val
                            && theBoard[ii][pos_key]->hasDone==false){
                        cout<< "POSKey+1 = " << pos_key-1<<","<<ii<<"=>"<< theBoard[ii][pos_key-1]->cell_val <<endl;
                        cout<< " POSKey = " << pos_key<<","<<ii<<"=>"<< theBoard[ii][pos_key]->cell_val<< endl;
                        combine2Cells(theBoard[ii][pos_key],theBoard[ii][pos_key-1]);
                        hasMoved = true;
                        pos_key++;
                    }
                    pos_key = pos_key-1;
                }
            }
        }
    }
}

bool Board::checkGameEnd(){
    for(int ii = 3; ii >= 0; ii--){
        for (int jj = 3; jj >=0; jj--){
            if(theBoard[ii][jj]->cell_val==0){
                 cout<<"i="<<ii<<" j="<<jj;
                cout<<" CHECk == 0"<<endl;
                return false;
            }

            if(theBoard[ii][jj]->cell_val!=0){
                if(ii-1==-1 || jj-1==-1){
                    continue;
                }
                if(theBoard[ii][jj]->cell_val==theBoard[ii][jj-1]->cell_val ||
                        theBoard[ii][jj]->cell_val==theBoard[ii-1][jj]->cell_val){
                     cout<<" //i="<<ii<<" j="<<jj<<"=>["<<ii<<","<<jj-1;
                    cout<<"] CHECk != 0";
                    cout<<" ["<<theBoard[ii][jj]->cell_val<<":"<<theBoard[ii][jj-1]->cell_val<<","<<theBoard[ii-1][jj]->cell_val<<"]"<<endl;
                   return false;
                }
            }
        }
    }
    cout<< "Get"<<endl;
    return true;
}


void Board::initBoard(){
    int posx1 =  rand()%4;//randomlly choose 0 -> 3
    int posx2 =  rand()%4;//randomlly choose 0 -> 3
    int posy1 =  rand()%4;//randomlly choose 0 -> 3
    int posy2 =  rand()%4;//randomlly choose 0 -> 3
    int choice[] = {2,4};
    int val1 = choice[rand()%2];
    int val2 = choice[rand()%2];
    while(posx1 == posx2 || posy1 == posy2){
        posx2 =  rand()%4;//randomlly choose 0 -> 3
        posy2 =  rand()%4;//randomlly choose 0 -> 3
    }

    theBoard[posx1][posy1]->cell_val = val1;
    theBoard[posx2][posy2]->cell_val = val2;
}
