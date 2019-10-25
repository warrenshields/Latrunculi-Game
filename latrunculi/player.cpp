#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

Player::Player(int id)
{
    _id = 1;
    _score = 0;
    _suicide = 0;
}

Player::Player()
{
    _id = 2;
    _score = 0;
    _suicide = 0;
}

void Player::movePiece(char board[][19], Board MyBoard, int score)
{
    cout<<"Player "<<GetID()<<" Score:"<<GetScore()<<endl;
    Referee referee;
    string pieceID, dest;
    char oldvalue;
    SelectPiece:
        cout<<"Player "<<GetID()<<' '<<"Select Piece:";
        cin>>pieceID;
        MyBoard.SetPieceID(pieceID);
        MyBoard.initPieceID();
        if(GetID()==1) ///Calls function which enforces rules on selection of pieces for player 1
        {
            referee.NoSelectCheat1(board, MyBoard);
            if(referee.GetAttemptedCheat()==1)
            {
                referee.SetAttemptedCheat(0); ///resetting attemptedCheat variable
                goto SelectPiece;
            }
        }
        else if(GetID()==2) ///Calls function which enforces rules on selection of pieces for player 2
        {

            referee.NoSelectCheat2(board, MyBoard);
            if(referee.GetAttemptedCheat()==1)
            {
                referee.SetAttemptedCheat(0); //resetting attemptedCheat variable
                goto SelectPiece;
            }
        }

        cout<<"Selected Piece at "<<'('<<MyBoard.GetRealY()<<','<<MyBoard.GetRealX()<<')'<<endl;
    MovePiece:
        cout<<"Where to move Piece?(-1 to cancel):";
        cin>>dest;
        MyBoard.SetDest(dest);
        MyBoard.initDest();
        if(MyBoard.GetDest() == "-1")
        {
            cout<<"Selected improper piece"<<endl;
            goto SelectPiece;
        }
        referee.NoMoveCheat(board, MyBoard); ///calling function that enforces rules on the movement of pieces
        if(referee.GetAttemptedCheat()==1)
        {
            referee.SetAttemptedCheat(0);
            goto MovePiece;
        }

        if(GetID()==1)
        {
            P1CapturePiece(board, MyBoard, score);
            P1ImmobilizePiece(board, MyBoard, score);
            P1CaptureDuke(board, MyBoard, score);
            P1DukeSuicide(board, MyBoard);
        }
        if(GetID()==2)
        {
            P2CapturePiece(board, MyBoard, score);
            P2ImmobilizePiece(board, MyBoard, score);
            P2CaptureDuke(board, MyBoard, score);
            P2DukeSuicide(board, MyBoard);
        }


        if(MyBoard.GetDest()!="-1")
        {
            oldvalue = board[MyBoard.GetY()][MyBoard.GetX()];
            board[MyBoard.GetY()][MyBoard.GetX()] = ' ';
            board[MyBoard.GetNewY()][MyBoard.GetNewX()] = oldvalue;
        }


    MyBoard.PrintBoard(board, 19, 19); ///Updates board after every move
    cout<<"Player "<<GetID()<<" Score:"<<GetScore()<<endl;
}

void Player::P1CapturePiece(char board[][19], Board MyBoard, int score)
{

    if((board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='o') && ///horizontal capture
            (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='x' || board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='X'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]= ' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='o') && ///horizontal capture
            (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='x' || board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='X'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='o') && ///vertical capture
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='X'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='o') && ///vertical capture
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='X'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
}

void Player::P2CapturePiece(char board[][19], Board MyBoard, int score)
{
    if((board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='x') && ///horizontal capture
            (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='o' || board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]= ' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='x') && ///horizontal capture
            (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='o' || board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='x') && ///vertical capture
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='O'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if((board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='x') && ///vertical capture
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='O'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
}


void Player::P1ImmobilizePiece(char board[][19], Board MyBoard, int score)
{
    if((board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='o') && ///top right corner
       ((MyBoard.GetNewX()+3)==18) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       ((MyBoard.GetNewY()-1)==2) )
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='o') &&
            ((MyBoard.GetNewX()+1)==18) && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (MyBoard.GetNewY()-3)==2)
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='o') && ///top left corner
            ((MyBoard.GetNewX()-3)==2) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ' ) &&
            (MyBoard.GetNewY()-1)==2)
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && ((MyBoard.GetNewX()-1)==2) &&
            ((MyBoard.GetNewY()-3)==2))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='o') && ///bottom right corner
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && ((MyBoard.GetNewX()+2)==17) && ((MyBoard.GetNewY()+1)==18))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17) && (MyBoard.GetNewY()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='o') && ///bottom left corner
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5) && (MyBoard.GetNewY()==17))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3) && (MyBoard.GetNewY()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='o') && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='o') && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='o') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }



}

void Player::P2ImmobilizePiece(char board[][19], Board MyBoard, int score)
{
    if((board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='x') && ///top right corner
       ((MyBoard.GetNewX()+3)==18) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       ((MyBoard.GetNewY()-1)==2) )
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='x') &&
            ((MyBoard.GetNewX()+1)==18) && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (MyBoard.GetNewY()-3)==2)
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='x') && ///top left corner
            ((MyBoard.GetNewX()-3)==2) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (MyBoard.GetNewY()-2)==3)
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ' ) && ((MyBoard.GetNewX()-1)==2) &&
            ((MyBoard.GetNewY()-3)==2))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='x') && ///bottom right corner
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && ((MyBoard.GetNewX()+2)==17) && ((MyBoard.GetNewY()+1)==18))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17) && (MyBoard.GetNewY()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='x') && ///bottom left corner
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5) && (MyBoard.GetNewY()==17))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3) && (MyBoard.GetNewY()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='x') && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        ScoreCounter(score);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='x') && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='x') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        ScoreCounter(score);
    }

}

void Player::P1CaptureDuke(char board[][19], Board MyBoard, int score)
{
    if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
       (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='O') && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==15))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
}

void Player::P2CaptureDuke(char board[][19], Board MyBoard, int score)
{
    if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
       (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&
       (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==5))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==3))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
     else if( (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') && (MyBoard.GetNewX()==17))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
    else if( (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') && (MyBoard.GetNewX()==17))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetScore(8);
    }
}

void Player::ScoreCounter(int score)
{
    if(GetScore()==0)
    {
        score++;
        SetScore(score);
    }
    else ///makes it so that the score will keep incrementing rather than reinitializing to 0
    {
        int currScore = GetScore();
        currScore++;
        SetScore(currScore);
    }
}

void Player::PlayerWins()
{
    cout<<"Player "<<GetID()<<" Wins!"<<endl;
}

void Player::P1DukeSuicide(char board[][19], Board MyBoard)
{
    if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='o' || ///surround from left
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='O' ) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1); ///sets bool true when a player captures their duke, resulting in the opponent's victory
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='O')
            &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ')
            &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='o' || ///surround from right
            board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='O') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
        else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='o' || ///surround from top
            board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
        else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='o' || ///surround from bottom
            board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='O') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (MyBoard.GetNewX()==5) && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='X') && (MyBoard.GetNewX()==5) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='O') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='O'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (MyBoard.GetNewX()==15) && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (MyBoard.GetNewX()==15) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='O'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='o' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='X') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='O'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }



}

void Player::P2DukeSuicide(char board[][19], Board MyBoard)
{
    if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='x' || ///surround from left
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]=='X' ) && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ') &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='X')
            &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' ')
            &&(board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='X'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='x' || ///surround from right
            board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='X') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
        else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-4]!=' ' ) &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='X'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='x' || ///surround from top
            board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='X') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
        else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='X'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='x' || ///surround from bottom
            board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='X') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='X') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='X'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (MyBoard.GetNewX()==5) && ///left wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='X') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=='O') && (MyBoard.GetNewX()==5) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='X'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()-2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='X') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='X'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
     else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==3) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='X'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (MyBoard.GetNewX()==15) && ///right wall hug
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]=='O') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]!=' '))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='x') && (board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=='X') && (MyBoard.GetNewX()==15) &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()+2]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='o' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()+2]=='O'))
    {
        board[MyBoard.GetNewY()][MyBoard.GetNewX()+2]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()-4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()-2][MyBoard.GetNewX()-2]=='X'))
    {
        board[MyBoard.GetNewY()-2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='x' || board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]=='X') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]!=' '))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }
    else if( (board[MyBoard.GetY()][MyBoard.GetX()]=='o') && (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=='O') && (MyBoard.GetNewX()==17) &&
            (board[MyBoard.GetNewY()+4][MyBoard.GetNewX()]!=' ') &&
            (board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='x' || board[MyBoard.GetNewY()+2][MyBoard.GetNewX()-2]=='X'))
    {
        board[MyBoard.GetNewY()+2][MyBoard.GetNewX()]=' ';
        SetSuicide(1);
    }



}
