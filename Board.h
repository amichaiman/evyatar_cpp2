//
// Created by evyatar on 11/9/18.
//

#ifndef EXCERCISE2_BOARD_H
#define EXCERCISE2_BOARD_H


#include <iostream>
#include<string>

#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board {
public:
    Board();
    virtual ~Board();
    void play();

private:
    typedef struct pair{
        pair(int first, int second){
            this->row = first;
            this->col = second;
        }
        pair(string other){
            this->other = other;
        }

        int row;
        int col;
        string other;
    } turnPair;

    typedef enum {A,B,C,D,E,F,G,H} column;
    static const char WHITE = 'W';
    static const char BLACK = 'B';
    static const char VACANT = 'o'; //empty
    static const int ROWS = 8;
    static const int COLUMNS = 8;
    char blackBoard[ROWS][COLUMNS];
    char currentPlayer;

    inline void invalidInput() const;
    inline void tie() const;

    void printBoardState();
    void initalizeBoard();
    bool boardFull();
    void win(char player) const;
    turnPair getInput();
    bool isValidMove(int row, int col);
    bool isValidDirection(int row, int col, int offsetI, int offsetJ);
    void updateBoard(turnPair spot);
    void flipColor(int row, int col, int offsetI, int offsetJ);
    bool isInBoard(int i);
    void declareWinner();
};

#endif // BOARD_H


#endif //EXCERCISE2_BOARD_H
