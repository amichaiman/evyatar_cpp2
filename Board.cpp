#include "Board.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Board::Board()
{
    currentPlayer = BLACK;
    for(int i=0 ; i < ROWS ; i++){
        for(int j=0 ; j < COLUMNS ; j++){
            blackBoard[i][j] = VACANT;
        }
    }
    // array - starts from zero
    initalizeBoard();
}

Board::~Board() {}

void Board::play(){
    bool passFlag = false;
    while(!boardFull()){
        printBoardState();
        cout << currentPlayer << ": ";
        turnPair spot = getInput();
        if (spot.other == "QUIT"){
            win(currentPlayer == BLACK ? WHITE : BLACK);
            return;
        }
        if (spot.other == "PASS") {
            if (passFlag == true){
                declareWinner();
                return;
            }
            passFlag = true;
        } else {
            updateBoard(spot);
            blackBoard[spot.row][spot.col] = currentPlayer;
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
                cout << BLACK << " ";
            }else if(blackBoard[i][j] == WHITE){
                cout << WHITE << " ";
            }else if(blackBoard[i][j] == VACANT){
                cout << "o" << " ";
            }
        }
        cout << endl;
    }
}

inline void Board::invalidInput() const { cout << "Invalid move; the game awaits a valid move." << endl; }
inline void Board::win(char player) const { cout << player << " wins the game" << endl; }
inline void Board::tie() const { cout << "The game ends in a tie." << endl; }
inline void Board::initalizeBoard() {
    blackBoard[E][3] = BLACK;
    blackBoard[D][4] = BLACK;
    blackBoard[E][4] = WHITE;
    blackBoard[D][3] = WHITE;
}

bool Board::boardFull() {
    for (int i=0; i<ROWS; i++){
        for (int j=0; j<COLUMNS; j++){
            if (blackBoard[i][j] != VACANT){
                return false;
            }
        }
    }
    return true;
}

Board::turnPair Board::getInput() {
    string input;

    cin >> input;

    if (input == "QUIT"){
        return turnPair("QUIT");
    }
    if (input == "PASS"){
        return turnPair("PASS");
    }
    if (!isInBoard(input[0]-'A') || !isInBoard(input[1]-'0'-1)){
        invalidInput();
        return getInput();
    }
    if (!isValidMove((input[1]-'0')-1,input[0]-'A')){
        invalidInput();
        return getInput();
    }
    cout << "3" << endl;
    return turnPair((input[1]-'0')-1, input[0]-'A');
}

bool Board::isInBoard(int i) {
    return i<COLUMNS && i>0;
}

bool Board::isValidMove(int row, int col) {
    int offsetI[] = { 1, 1, 1, 0, 0, -1,-1, -1};
    int offsetJ[] = {-1, 0, 1,-1, 1, -1, 0, 1};
    const int NUM_DIRECTIONS = 8;

    for (int i=0; i<NUM_DIRECTIONS; i++){
        if (isValidDirection(row, col, offsetI[i], offsetJ[i])){
            return true;
        }
    }
    return false;
}

bool Board::isValidDirection(int row, int col, int offsetI, int offsetJ) {
    if (blackBoard[row+offsetI][col+offsetJ] == (currentPlayer == BLACK ? WHITE : BLACK)) {
        row += offsetI;
        col +=offsetJ;

        while (isInBoard(row) && isInBoard(col)){
            if (blackBoard[row][col] == currentPlayer){
                return true;
            }
            if (blackBoard[row][col] == VACANT) {
                return false;
            }
            row +=offsetI;
            col +=offsetJ;
        }
    }
    return false;
}

void Board::updateBoard(Board::turnPair spot) {
    int offsetI[] = { 1, 1, 1, 0, 0, -1,-1, -1};
    int offsetJ[] = {-1, 0, 1,-1, 1, -1, 0, 1};
    const int NUM_DIRECTIONS = 8;

    for (int i=0; i<NUM_DIRECTIONS; i++){
        if (isValidDirection(spot.row, spot.col, offsetI[i], offsetJ[i])){
            flipColor(spot.row, spot.col, offsetI[i], offsetJ[i]);
        }
    }
}

void Board::flipColor(int row, int col, int offsetI, int offsetJ) {
    row += offsetI;
    col += offsetJ;
    while (blackBoard[row][col] != currentPlayer){
        blackBoard[row][col] = currentPlayer;
        row += offsetI;
        col += offsetJ;
    }
}

void Board::declareWinner() {
    int blackCount = 0;
    int whiteCount = 0;

    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLUMNS; j++){
            if (blackBoard[i][j] == BLACK){
                blackCount++;
            } else if(blackBoard[i][j] == WHITE){
                whiteCount++;
            }
        }
    }
    if (blackCount == whiteCount){
        tie();
    } else {
        win(blackCount > whiteCount ? BLACK : WHITE);
    }
}
