//
// Created by amichai on 16/11/18.
//

#ifndef EVYATER_CPP2_RULES_H
#define EVYATER_CPP2_RULES_H

#include "BoardLocation.h"
class Board;

class Rules {
public:
    Rules();
    virtual ~Rules();
    static bool boardFull(Board *blackBoard);
    static BoardLocation getInput(Board *blackBoard);
    static bool isInBoard(int i);
    static void invalidInput();
    static void win(char player);
    static void updateBoard(Board *blackBoard, const BoardLocation &spot);
    static void declareWinner(Board *blackBoard);
private:
    static bool isValidMove(Board *blackBoard, int row, int col);
    static bool isValidDirection(Board *blackBoard, int row, int col, int offsetI, int offsetJ);
    static void flipColor(Board *blackBoard, int row, int col, int offsetI, int offsetJ);
    static void tie();

};


#endif //EVYATER_CPP2_RULES_H
