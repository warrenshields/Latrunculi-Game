#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

class Board
 {
    public:
        Board();
        void MakeBoard(char board[][19], int x, int y);
        void PrintBoard(char board[][19], int x, int y);
        void initBoard(char board[][19], int x, int y);
        void initPieceID();
        void initDest();

        char GetP1Piece(){return _p1Piece;}
        void SetP1Piece(char p1Piece){_p1Piece = p1Piece;}

        char GetP1Duke(){return _p1Duke;}
        void SetP1Duke(char p1Duke){_p1Duke = p1Duke;}

        char GetP2Piece(){return _p2Piece;}
        void SetP2Piece(char p2Piece){_p2Piece = p2Piece;}

        char GetP2Duke(){return _p2Duke;}
        void SetP2Duke(char p2Duke){_p2Duke = p2Duke;}

        string GetPieceID(){return _pieceID;}
        void SetPieceID(string pieceID){_pieceID = pieceID;}

        string GetDest(){return _dest;}
        void SetDest(string dest){_dest = dest;}

        int GetX(){return _x;}
        void SetX(int x){_x = x;}

        int GetY(){return _y;}
        void SetY(int y){_y = y;}

        int GetNewX(){return _newX;}
        void SetNewX(int newX){_newX = newX;}

        int GetNewY(){return _newY;}
        void SetNewY(int newY){_newY = newY;}

        int GetRealX(){return _realX;}
        void SetRealX(int realX){_realX = realX;}

        int GetRealY(){return _realY;}
        void SetRealY(int realY){_realY = realY;}


    private:
        char _p1Piece;
        char _p1Duke;
        char _p2Piece;
        char _p2Duke;
        string _pieceID;
        string _dest;
        int _x;
        int _y;
        int _newX;
        int _newY;
        int _realX;
        int _realY;

 };



#endif // BOARD_H_INCLUDED
