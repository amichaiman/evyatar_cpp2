#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Rules.h"
#include "BoardLocation.h"

using namespace std;

Board::Board() {
    currentPlayer = BLACK;
    for(int i=0 ; i < ROWS ; i++){
        for(int j=0 ; j < COLUMNS ; j++){
            blackBoard[i][j] = VACANT;
        }
    }
    initializeBoard();
}

Board::~Board() {}

void Board::play(){
    bool passFlag = false;
    while(!Rules::boardFull(this)){
        printBoardState();
        cout << currentPlayer << ":" << endl;
        BoardLocation spot = Rules::getInput(this);
        if (spot.getOther() == "QUIT"){
            cout << currentPlayer << ": QUIT" << endl;
            Rules::win(currentPlayer == BLACK ? WHITE : BLACK);
            return;
        }
        if (spot.getOther() == "PASS") {
            if (passFlag){
                Rules::declareWinner(this);
                return;
            }
            passFlag = true;
        } else {
            Rules::updateBoard(this,spot);
            blackBoard[spot.getRow()][spot.getCol()] = currentPlayer;
            passFlag = false;
        }
        currentPlayer = currentPlayer == BLACK ? WHITE : BLACK;
    }
}
/*prints the board state*/
void Board::printBoardState(){
    for(int i=0 ; i < ROWS ; i++){
        for(int j=0 ; j < COLUMNS ; j++){
            if(blackBoard[i][j] == BLACK){
                cout << BLACK << (j == COLUMNS-1 ? "" : " ");
            }else if(blackBoard[i][j] == WHITE){
                cout << WHITE << (j == COLUMNS-1 ? "" : " ");
            }else if(blackBoard[i][j] == VACANT){
                cout << "O" << (j == COLUMNS-1 ? "" : " ");
            }
        }
        cout << endl;
    }
}

inline void Board::initializeBoard() {
    blackBoard[E][3] = BLACK;
    blackBoard[D][4] = BLACK;
    blackBoard[E][4] = WHITE;
    blackBoard[D][3] = WHITE;
}

int Board::getValue(const int i,const int j) const {
    return blackBoard[i][j];
}

char Board::getCurrentPlayer() {
    return currentPlayer;
}

void Board::setValue(int i, int j, char value) {
    blackBoard[i][j] = value;
}
