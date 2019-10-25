#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

Board::Board()
{
    _p1Piece = ' ';
    _p2Piece = ' ';
    _p1Duke = ' ';
    _p2Duke = ' ';
}

void Board::initBoard(char board[][19], int x, int y) ///initializes the pieces on the board
{
    char p1Piece = 'x';
    char p1Duke = 'X';
    char p2Piece = 'o';
    char p2Duke = 'O';

    SetP1Piece(p1Piece);
    SetP1Duke(p1Duke);
    SetP2Piece(p2Piece);
    SetP2Duke(p2Duke);

    for(int i = 0; i<y; i++)
    {
        for(int j = 0; j<x; j++)
        {
            board[i][j] = ' ';
        }
    }

    for(int i = 3; i<=3; i++)
    {
        for(int j = 2; j<x; j++)
        {
            if((j%2)!=0){board[i][j]=GetP1Piece();}
        }
    }

    board[5][9]=GetP1Duke();

    for(int i = 17; i<=17; i++)
    {
        for(int j = 2; j<x; j++)
        {
            if((j%2)!=0){board[i][j]=GetP2Piece();}
        }
    }

    board[15][11]=GetP2Duke();

}

void Board::MakeBoard(char board[][19], int x, int y) ///creates the board
{

    board[0][3]='0';
    board[0][5]='1';
    board[0][7]='2';
    board[0][9]='3';
    board[0][11]='4';
    board[0][13]='5';
    board[0][15]='6';
    board[0][17]='7';

    board[3][0]='a';
    board[5][0]='b';
    board[7][0]='c';
    board[9][0]='d';
    board[11][0]='e';
    board[13][0]='f';
    board[15][0]='g';
    board[17][0]='h';

    for(int i = 2; i<y; i++)
    {
        if((i%2)==0)
        {
            for(int j = 2; j<x; j++)
            {
                board[i][j] = '-';
            }
        }
    }

    for(int i = 3; i<y; i++)
    {
        if((i%2)!=0)
        {
            for(int j = 2; j<x; j++)
            {
                if((j%2)==0){board[i][j]='|';}
            }
        }
    }

}

void Board::PrintBoard(char board[][19], int x, int y)
{
    system("cls");
    MakeBoard(board, 19, 19);
    for(int i = 0; i<y; i++)
    {
        for(int j = 0; j<x; j++)
        {
            cout<<board[i][j];
        }
        cout<<endl;
    }
}

void Board::initPieceID() ///initializes a piece's current position
{
    int x, y, realX, realY; ///realX and realY represent the the values that the board are supposed to be representing
    if(GetPieceID().substr(0,1)=="a")
    {
         y = 3;
         realY = 0;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="b")
    {
         y = 5;
         realY = 1;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="c")
    {
         y = 7;
         realY = 2;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="d")
    {
         y = 9;
         realY = 3;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="e")
    {
         y = 11;
         realY = 4;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="f")
    {
         y = 13;
         realY = 5;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="g")
    {
         y = 15;
         realY = 6;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
    else if(GetPieceID().substr(0,1)=="h")
    {
         y = 17;
         realY = 7;
        SetY(y);
        SetRealY(realY);
        if(GetPieceID().substr(1,1)=="0")
        {
             x = 3;
             realX = 0;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="1")
        {
             x = 5;
             realX = 1;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="2")
        {
             x = 7;
             realX = 2;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="3")
        {
             x = 9;
             realX = 3;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="4")
        {
             x = 11;
             realX = 4;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="5")
        {
             x = 13;
             realX = 5;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="6")
        {
             x = 15;
             realX = 6;
            SetX(x);
            SetRealX(realX);
        }
        else if(GetPieceID().substr(1,1)=="7")
        {
             x = 17;
             realX = 7;
            SetX(x);
            SetRealX(realX);
        }
    }
}

void Board::initDest() ///initializes a piece's destination
{
    int newY, newX;
    if(GetDest().substr(0,1)=="a")
    {
        newY = 3;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="b")
    {
        newY = 5;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="c")
    {
        newY = 7;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="d")
    {
        newY = 9;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="e")
    {
        newY = 11;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="f")
    {
        newY = 13;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="g")
    {
        newY = 15;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
    else if(GetDest().substr(0,1)=="h")
    {
        newY = 17;
        SetNewY(newY);
        if(GetDest().substr(1,1)=="0")
        {
            int newX = 3;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="1")
        {
            newX = 5;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="2")
        {
            newX = 7;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="3")
        {
            newX = 9;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="4")
        {
            newX = 11;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="5")
        {
            newX = 13;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="6")
        {
            newX = 15;
            SetNewX(newX);
        }
        else if(GetDest().substr(1,1)=="7")
        {
            newX = 17;
            SetNewX(newX);
        }
    }
}
