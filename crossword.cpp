/*
Your solution may ONLY use the C++ header files listed below
program: A2main.cpp
author:  danny abesdris
date:    november 15, 2022
purpose: C++ main( ) program for PRG355 Fall 2022 assignment #2
*/


#include <iostream>
#include <cstring>
#include <new>
using namespace std;

class Crossword {
private:
    char board[35][35], mask[35][35];
    int score;
    char *playerName;
    char coord[3];
public:
    Crossword( );
    Crossword(const char *name);
    void loadWord(const char *coord, const char *word, char dir);
    void updateGameBoard(const char *coord);
    friend ostream& operator<<(ostream &os, Crossword &r);
    ~Crossword( );
};


int main( ) {
    Crossword ts, ed("Edsgar Dijkstra");

    ts.loadWord("D7", "DEFAULT", 'H');
    ts.loadWord("DC", "LOADED", 'V');
    ts.loadWord("8T", "GAME", 'H');

    ed.loadWord("AG", "SCIENTIST", 'H');
    ed.loadWord("V2", "ELEGANT", 'H');
    ed.loadWord("P2", "COMPUTER", 'V');

    cout << ts << ed << endl; // should call stream operator<<( ) friend function
                             // to display initial empty game boards (containing only '.' and titles).



    ts.updateGameBoard("55"); // no letter found at 55
    ts.updateGameBoard("8V"); // should find 'M' at 8V and then also find 'E', 'A', 'G'
                             // and update score to 20 points

    ts.updateGameBoard("FC"); // should find 'A' at FC and then also find the remaining chars
                             // 'D', 'E', 'D', 'O', 'L' and update score to 50 points


    ed.updateGameBoard("V2"); // should find 'E' at V2 and then also the characters, "LEGANT"
                             // and "COMPUTER" by searching both horizontally and vertically at
                             // that location and update score to 70 points (does not count 'E' twice)!
   return 0;
}



// YOUR CODE BELOW...


Crossword::Crossword() {
    for (int i = 0; i < 35; i++)
        for (int j = 0; j < 35; j++)
            board[i][j] = mask[i][j] = '.';
    playerName = new char[strlen("Tom Swift") + 1];
    coord[0] = '\0';
    score = 0;
    strcpy(playerName, "Tom Swift");
}

Crossword::Crossword(const char *name) {
    for (int i = 0; i < 35; i++)
        for (int j = 0; j < 35; j++)
            board[i][j] = mask[i][j] = '.';
    playerName = new char[strlen(name) + 1];
    coord[0] = '\0';
    score = 0;
    strcpy(playerName, name);
}

// helper
int getIndexFromCoord(char c) {
    if (c >= '1' && c <= '9')
        return c - '0' - 1;
    else
        return c - 'A' + 9;
}

char getCoordFromIndex(int i) {
    if (i < 9)
        return i + '1';
    else
        return 'A' + i - 9;
}

void Crossword::loadWord(const char *coord, const char *word, char dir) {
    int i = 0;
    int r = getIndexFromCoord(coord[0]);
    int c = getIndexFromCoord(coord[1]);
    
    if (dir == 'V') {
        while (word[i]) {
            board[r][c] = word[i];
            r++; i++;
        }
    }
    else {
        while (word[i]) {
            board[r][c] = word[i];
            c++; i++;
        }
    }
}

void Crossword::updateGameBoard(const char *coord) {
    int x = getIndexFromCoord(coord[0]);
    int y = getIndexFromCoord(coord[1]);
    
    strcpy(this->coord, coord);
    if (board[x][y] == '.') {
        mask[x][y] = '~';
        cout << *this;
        return;
    }
    
    mask[x][y] = board[x][y];
    score += 5;
    
    x = getIndexFromCoord(coord[0]);
    y = getIndexFromCoord(coord[1]);
    while (--x >= 0 && board[x][y] != '.') {
        mask[x][y] = board[x][y];
        score += 5;
    }
    
    x = getIndexFromCoord(coord[0]);
    y = getIndexFromCoord(coord[1]);
    while (--y >= 0 && board[x][y] != '.') {
        mask[x][y] = board[x][y];
        score += 5;
    }
    
    x = getIndexFromCoord(coord[0]);
    y = getIndexFromCoord(coord[1]);
    while (++x < 35 && board[x][y] != '.') {
        mask[x][y] = board[x][y];
        score += 5;
    }
    
    x = getIndexFromCoord(coord[0]);
    y = getIndexFromCoord(coord[1]);
    while (++y < 35 && board[x][y] != '.') {
        mask[x][y] = board[x][y];
        score += 5;
    }
    cout << *this;
}

ostream& operator<<(ostream &os, Crossword &r) {
    os << "\n  C++ Crossword Puzzle... By: " << r.playerName << endl;
    os << "  123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" << endl;
    for (int i = 0; i < 35; i++) {
        os << getCoordFromIndex(i) << "|";
        for (int j = 0; j < 35; j++)
            os << r.mask[i][j];
        os << "|" << endl;
    }
    
    int row = getIndexFromCoord(r.coord[0]);
    int col = getIndexFromCoord(r.coord[1]);
    
    os << "Current Score:";
    if (r.score < 10)
        os << "000";
    else if (r.score < 100)
        os << "00";
    else if (r.score < 1000)
        os << "0";
    os << r.score;
    os << "  Last Move: ";
    if (r.coord[0] == '\0')
        os << "NA" << endl;
    else if (r.board[row][col] == '.')
        os << "NO letter FOUND at '[" << r.coord[0] << "," << r.coord[1] << "]'" << endl;
    else
        os << "FOUND '" << r.board[row][col] << "' at '[" << r.coord[0] << "," << r.coord[1] << "]'" << endl;
    return os;
}

Crossword::~Crossword() {
    delete[] playerName;
}

