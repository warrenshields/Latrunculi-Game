#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

 class Player
 {
    public:
        Player(int id); ///2 player objects created
        Player();
        void movePiece(char board[][19], Board MyBoard, int score);
        void P1CapturePiece(char board[][19], Board MyBoard, int score);
        void P2CapturePiece(char board[][19], Board MyBoard, int score);
        void P1ImmobilizePiece(char board[][19], Board MyBoard, int score);
        void P2ImmobilizePiece(char board[][19], Board MyBoard, int score);
        void P1CaptureDuke(char board[][19], Board MyBoard, int score);
        void P2CaptureDuke(char board[][19], Board MyBoard, int score);
        void P1DukeSuicide(char board[][19], Board MyBoard);
        void P2DukeSuicide(char board[][19], Board MyBoard);
        void ScoreCounter(int score);
        void PlayerWins();

        int GetID(){return _id;}
        void setID(int id){_id = id;}

        int GetScore(){return _score;}
        void SetScore(int score){_score = score;}

        bool GetSuicide(){return _suicide;}
        void SetSuicide(bool suicide){_suicide = suicide;}


    private:
       int _id;
       int _score;
       bool _suicide;

 };



#endif // PLAYER_H_INCLUDED
