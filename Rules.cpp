//
// Created by amichai on 16/11/18.
//

#include "Rules.h"
#include "Board.h"
#include <iostream>
using namespace std;

inline void Rules::invalidInput() { cout << "Invalid move; the game awaits a valid move." << endl; }
inline void Rules::win(char player) { cout << player << " wins the game." << endl; }
inline void Rules::tie() { cout << "The game ends in a tie." << endl; }

bool Rules::boardFull(Board *blackBoard) {
    for (int i=0; i<Board::COLUMNS; i++){
        for (int j=0; j<Board::ROWS; j++){
            if (blackBoard->getValue(i,j) == Board::VACANT){
                return false;
            }
        }
    }
    return true;
}

BoardLocation Rules::getInput(Board *blackBoard) {
    string input;

    cin >> input;

    if (input == "QUIT"){
        return BoardLocation("QUIT");
    }
    if (input == "PASS"){
        return BoardLocation("PASS");
    }
    if (!isInBoard(input[0]-'A') || !isInBoard(input[1]-'0'-1)){
        invalidInput();
        return getInput(blackBoard);
    }
    if (!isValidMove(blackBoard, (input[1] - '1'), input[0] - 'A')){
        invalidInput();
        return getInput(blackBoard);
    }
    return BoardLocation((input[1]-'0')-1, input[0]-'A');
}

bool Rules::isInBoard(int i) {
    return i<Board::COLUMNS && i>0;
}

bool Rules::isValidMove(Board *blackBoard, int row, int col) {
    int offsetI[] = { 1, 1, 1, 0, 0, -1,-1, -1};
    int offsetJ[] = {-1, 0, 1,-1, 1, -1, 0, 1};
    const int NUM_DIRECTIONS = 8;

    for (int i=0; i<NUM_DIRECTIONS; i++){
        if (isValidDirection(blackBoard, row, col, offsetI[i], offsetJ[i])){
            return true;
        }
    }
    return false;
}

bool Rules::isValidDirection(Board *blackBoard, int row, int col, int offsetI, int offsetJ) {
    if (blackBoard->getValue(row+offsetI,col+offsetJ) == (blackBoard->getCurrentPlayer() == Board::BLACK ? Board::WHITE : Board::BLACK)) {
        row += offsetI;
        col +=offsetJ;

        while (isInBoard(row) && isInBoard(col)){
            if (blackBoard->getValue(row+offsetI,col+offsetJ) == blackBoard->getCurrentPlayer()){
                return true;
            }
            if (blackBoard->getValue(row+offsetI,col+offsetJ) == Board::VACANT) {
                return false;
            }
            row +=offsetI;
            col +=offsetJ;
        }
    }
    return false;
}

void Rules::updateBoard(Board* blackBoard, const BoardLocation &spot) {
    int offsetI[] = { 1, 1, 1, 0, 0, -1,-1, -1};
    int offsetJ[] = {-1, 0, 1,-1, 1, -1, 0, 1};
    const int NUM_DIRECTIONS = 8;

    for (int i=0; i<NUM_DIRECTIONS; i++){
        if (isValidDirection(blackBoard, spot.getRow(), spot.getCol(), offsetI[i], offsetJ[i])){
            flipColor(blackBoard, spot.getRow(), spot.getCol(), offsetI[i], offsetJ[i]);
        }
    }
}
void Rules::flipColor(Board* blackBoard, int row, int col, int offsetI, int offsetJ) {
    row += offsetI;
    col += offsetJ;
    while (blackBoard->getValue(row,col) != blackBoard->getCurrentPlayer()){
        blackBoard->setValue(row, col, blackBoard->getCurrentPlayer());
        row += offsetI;
        col += offsetJ;
    }
}

void Rules::declareWinner(Board* blackBoard) {
    int blackCount = 0;
    int whiteCount = 0;

    for (int i=0; i<Board::ROWS; i++) {
        for (int j=0; j<Board::COLUMNS; j++){
            if (blackBoard->getValue(i,j) == Board::BLACK){
                blackCount++;
            } else if(blackBoard->getValue(i,j) == Board::WHITE){
                whiteCount++;
            }
        }
    }
    if (blackCount == whiteCount){
        tie();
    } else {
        win(blackCount > whiteCount ? Board::BLACK : Board::WHITE);
    }
}

Rules::Rules() {}

Rules::~Rules() {

}
