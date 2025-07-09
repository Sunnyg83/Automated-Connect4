// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
using namespace std;

class HumanPlayerImpl
{
  public:
    HumanPlayerImpl(HumanPlayer* p);
    int chooseMove(const Scaffold& s, int N, int color);
  private:
    HumanPlayer* m_player;
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

HumanPlayerImpl::HumanPlayerImpl(HumanPlayer* p)
 : m_player(p)
{}
// Human player choose move

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col;
    while (true) {
        cout << "Enter column: (1-" << s.cols() << "):" << endl;
        cin >> col;
        if (col >= 1 && col <= s.cols() && s.checkerAt(col, s.levels()) == VACANT)
            return col;
        cout << "Invalid move. Try again." << endl;
    }
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    // insert into the left most column that you can actually insert into
    for (int col = 1; col <= s.cols(); col++) {
        if(s.checkerAt(col, s.levels()) == VACANT) {
            return col;
        }
    }
    return 0;
}

const int BIGNUM = 100000;




int minimax(Scaffold& board, int N, int depth, int currentColor, int smartColor, int& bestMove) {
    int winner;
    if (isDone(board, N, winner)) {
        if (winner == smartColor)
            return BIGNUM - depth;
        if (winner == opp(smartColor))
            return -BIGNUM + depth;
        return 0; // tie
    }
    int bestScore;
    if(currentColor == smartColor)
        bestScore = -BIGNUM;
    else
        bestScore = BIGNUM;

    for (int col = 1; col <= board.cols(); ++col) {
        if (board.checkerAt(col, board.levels()) != VACANT)
            continue;
        board.makeMove(col, currentColor);
        int dummyMove = 0;
        int score = minimax(board, N, depth + 1, opp(currentColor), smartColor, dummyMove);
        board.undoMove();

        if (currentColor == smartColor) {
            if (score > bestScore) {
                bestScore = score;
                bestMove = col;
            }
        } else {
            if (score < bestScore) {
                bestScore = score;
                bestMove = col;
            }
        }
    }
    return bestScore;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color) {
    Scaffold copy = s;  // work on copy
    int bestCol = 1;
    minimax(copy, N, 0, color, color, bestCol);
    return bestCol;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.  You should
//  not change any of the code from here to the end of this file.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl(this);
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}


