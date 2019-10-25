#ifndef REFEREE_H_INCLUDED
#define REFEREE_H_INCLUDED
#include <iostream>
#include <bits/stdc++.h>
#include "player.h"
#include "referee.h"
#include "board.h"
#include <string>

using namespace std;

class Referee
 {
    public:
        Referee();
        void PlayGame();
        void NoSelectCheat1(char board[][19], Board MyBoard);
        void NoSelectCheat2(char board[][19], Board MyBoard);
        void NoMoveCheat(char board[][19], Board MyBoard);

        bool GetAttemptedCheat(){return _attemptedCheat;}
        void SetAttemptedCheat(bool attemptedCheat){_attemptedCheat = attemptedCheat;}

    private:
        bool _attemptedCheat;

 };


#endif // REFEREE_H_INCLUDED
