//
// Created by amichai on 16/11/18.
//

#ifndef EVYATER_CPP2_BOARDLOCATION_H
#define EVYATER_CPP2_BOARDLOCATION_H
#include <string>
using namespace std;

class BoardLocation {
public:
    BoardLocation(int first, int second);
    BoardLocation(const string &other);
    int getRow() const;
    int getCol() const;
    const string &getOther() const;
private:
    int row;
    int col;
    string other;

};
#endif //EVYATER_CPP2_BOARDLOCATION_H
