//
// Created by amichai on 16/11/18.
//

#include "BoardLocation.h"

BoardLocation::BoardLocation(int first, int second) {
    this->row = first;
    this->col = second;
    other = "";
}

BoardLocation::BoardLocation(const string &other) {
    this->other = other;
    row = col = 0;
}

int BoardLocation::getRow() const {
    return row;
}

int BoardLocation::getCol() const {
    return col;
}

const string &BoardLocation::getOther() const {
    return other;
}

