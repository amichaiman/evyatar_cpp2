//
// Created by evyatar on 11/9/18.
//

#ifndef EXCERCISE2_BOARD_H
#define EXCERCISE2_BOARD_H


#include <iostream>
#include<string>
#include "BoardLocation.h"

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
public:
    Board();
    virtual ~Board();

    void play();
    static const int ROWS = 8;
    static const int COLUMNS = 8;
    static const char VACANT = 'o';
    static const char WHITE = 'W';
    static const char BLACK = 'B';

    int getValue(int i, int j) const;
    char getCurrentPlayer();
    void setValue(int i, int j, char value);

private:
    typedef enum {A,B,C,D,E,F,G,H} column;
    char blackBoard[ROWS][COLUMNS];
    char currentPlayer;
    void printBoardState();
    void initializeBoard();
};

#endif // BOARD_H


#endif //EXCERCISE2_BOARD_H
