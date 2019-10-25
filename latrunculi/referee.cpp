#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

Referee::Referee()
{
    _attemptedCheat = 0;
}

void Referee::PlayGame()
{
    int id;
    int score = 0;
    Board MyBoard;
    Player p1(id);
    Player p2;
    char board[19][19];
    MyBoard.initBoard(board, 19, 19);
    MyBoard.PrintBoard(board, 19, 19);
    while(p1.GetScore()!=8 && p2.GetScore()!=8) ///the game will loop until a player reaches 8 points
    {
        p1.movePiece(board, MyBoard, score);
        if(p1.GetSuicide()==1) ///if player one captures his own duke player two wins
        {
            p2.SetScore(8);
        }
        if(p1.GetScore()==8 || p2.GetScore()==8)
            break;
        p2.movePiece(board, MyBoard, score);
        if(p2.GetSuicide()==1) ///if player two captures his own duke, player one wins
        {
            p1.SetScore(8);
        }
        if(p2.GetScore()==8 || p1.GetScore()==8)
            break;
    }
    if(p1.GetScore()==8 || p2.GetScore()==8) ///calls winner of game
    {
        if(p1.GetScore()==8)
        {
            p1.PlayerWins();
        }
        if(p2.GetScore()==8)
        {
            p2.PlayerWins();
        }
    }

}

void Referee::NoSelectCheat1(char board[][19], Board MyBoard)
{
    bool attemptedCheat;
    if(MyBoard.GetPieceID().substr(0,1)!="a" && MyBoard.GetPieceID().substr(0,1)!="b" && MyBoard.GetPieceID().substr(0,1)!="c" && MyBoard.GetPieceID().substr(0,1)!="d" &&
           MyBoard.GetPieceID().substr(0,1)!="e" && MyBoard.GetPieceID().substr(0,1)!="f" && MyBoard.GetPieceID().substr(0,1)!="g" && MyBoard.GetPieceID().substr(0,1)!="h")
    {
        cout<<"You did not choose a real piece"<<endl; ///Player may only choose the given y coords
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat); ///sets bool variable to true when player cheats which prompts the user to re-enter
    }
    else if(MyBoard.GetPieceID().substr(1,1)!="0" && MyBoard.GetPieceID().substr(1,1)!="1" && MyBoard.GetPieceID().substr(1,1)!="2" && MyBoard.GetPieceID().substr(1,1)!="3" && MyBoard.GetPieceID().substr(1,1)!="4"
       && MyBoard.GetPieceID().substr(1,1)!="5" && MyBoard.GetPieceID().substr(1,1)!="6" && MyBoard.GetPieceID().substr(1,1)!="7")
    {
        cout<<"You did not choose a real piece"<<endl; ///Player may only choose the give x coords
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
    else if(board[MyBoard.GetY()][MyBoard.GetX()]=='o' || board[MyBoard.GetY()][MyBoard.GetX()]=='O') ///REF: player can only move his piece
    {
        cout<<"You tried to select the opponent's piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
    else if(board[MyBoard.GetY()][MyBoard.GetX()]==' ') ///REF: player chose an empty space
    {
        cout<<"You did not choose a piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
}

void Referee::NoSelectCheat2(char board[][19], Board MyBoard)
{
    bool attemptedCheat;
    if(MyBoard.GetPieceID().substr(0,1)!="a" && MyBoard.GetPieceID().substr(0,1)!="b" && MyBoard.GetPieceID().substr(0,1)!="c" && MyBoard.GetPieceID().substr(0,1)!="d" &&
           MyBoard.GetPieceID().substr(0,1)!="e" && MyBoard.GetPieceID().substr(0,1)!="f" && MyBoard.GetPieceID().substr(0,1)!="g" && MyBoard.GetPieceID().substr(0,1)!="h")
    {
        cout<<"You did not choose a real piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
    else if(MyBoard.GetPieceID().substr(1,1)!="0" && MyBoard.GetPieceID().substr(1,1)!="1" && MyBoard.GetPieceID().substr(1,1)!="2" && MyBoard.GetPieceID().substr(1,1)!="3" && MyBoard.GetPieceID().substr(1,1)!="4" &&
            MyBoard.GetPieceID().substr(1,1)!="5" && MyBoard.GetPieceID().substr(1,1)!="6" && MyBoard.GetPieceID().substr(1,1)!="7")
    {
        cout<<"You did not choose a real piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
    else if(board[MyBoard.GetY()][MyBoard.GetX()]=='x' || board[MyBoard.GetY()][MyBoard.GetX()]=='X') ///REF: player can only move his piece
    {
        cout<<"You tried to select the opponent's piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
    else if(board[MyBoard.GetY()][MyBoard.GetX()]==' ') ///REF: player chose an empty space
    {
        cout<<"You did not choose a piece"<<endl;
        attemptedCheat = 1;
        SetAttemptedCheat(attemptedCheat);
    }
}

void Referee::NoMoveCheat(char board[][19], Board MyBoard)
{
    if(MyBoard.GetDest().substr(0,1)!="a" && MyBoard.GetDest().substr(0,1)!="b" && MyBoard.GetDest().substr(0,1)!="c" && MyBoard.GetDest().substr(0,1)!="d" &&
       MyBoard.GetDest().substr(0,1)!="e" && MyBoard.GetDest().substr(0,1)!="f" && MyBoard.GetDest().substr(0,1)!="g" && MyBoard.GetDest().substr(0,1)!="h")
    {
        cout<<"Invalid destination"<<endl;
        SetAttemptedCheat(1);
    }
    else if(MyBoard.GetDest().substr(1,1)!="0" && MyBoard.GetDest().substr(1,1)!="1" && MyBoard.GetDest().substr(1,1)!="2" && MyBoard.GetDest().substr(1,1)!="3" && MyBoard.GetDest().substr(1,1)!="4" && MyBoard.GetDest().substr(1,1)!="5"
       && MyBoard.GetDest().substr(1,1)!="6" && MyBoard.GetDest().substr(1,1)!="7")
    {
        cout<<"Invalid destination"<<endl;
        SetAttemptedCheat(1);
    }
    else if(MyBoard.GetY()!=MyBoard.GetNewY() && MyBoard.GetX()!=MyBoard.GetNewX()) ///REF: Player can only move horizontal and vertical
    {
        cout<<"Illegal Move"<<endl;
        SetAttemptedCheat(1);
    }
    else if(MyBoard.GetY()>MyBoard.GetNewY()) ///Player cannot vertically pass through a piece from the bottom
    {
        for(int i = MyBoard.GetNewY(); i<MyBoard.GetY(); i+=2)
        {
            if(board[i][MyBoard.GetNewX()]!=' ')
            {
                SetAttemptedCheat(1);
                if(GetAttemptedCheat()==1){cout<<"That path is blocked"<<endl;}
            }
        }
    }
    else if(MyBoard.GetY()<MyBoard.GetNewY()) ///Player cannot vertically pass through a piece from the top
    {
        for(int i = MyBoard.GetNewY(); i>MyBoard.GetY(); i-=2)
        {
            if(board[i][MyBoard.GetNewX()]!=' ')
            {
                SetAttemptedCheat(1);
                if(GetAttemptedCheat()==1){cout<<"That path is blocked"<<endl;}
            }
        }
    }
    else if(MyBoard.GetX()>MyBoard.GetNewX()) ///Player cannot horizontally pass through a piece from the right
    {
        for(int i = MyBoard.GetNewX(); i<MyBoard.GetX(); i+=2)
        {
           if(board[MyBoard.GetNewY()][i]!=' ')
           {
               SetAttemptedCheat(1);
               if(GetAttemptedCheat()==1){cout<<"That path is blocked"<<endl;}
           }
        }
    }
    else if(MyBoard.GetX()<MyBoard.GetNewX()) ///Player cannot horizontally through a piece from the left
    {
        for(int i = MyBoard.GetNewX(); i>MyBoard.GetX(); i-=2)
        {
            if(board[MyBoard.GetNewY()][i]!=' ')
            {
                SetAttemptedCheat(1);
                if(GetAttemptedCheat()==1){cout<<"That path is blocked"<<endl;}
            }
        }
    }

    else if((board[MyBoard.GetNewY()][MyBoard.GetNewX()])!=' ') ///REF: Player cannot move into occupied position
    {
        cout<<"That space is taken"<<endl;
        SetAttemptedCheat(1);
    }


}
