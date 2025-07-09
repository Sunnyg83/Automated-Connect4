#include "provided.h"

#include "support.h"
#include <iostream>
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
private:
    Scaffold mScaffold;
    int mN;
    Player* mRed;
    Player* mBlack;
    int mTurn;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black): mScaffold(nColumns, nLevels), mN(N), mRed(red), mBlack(black), mTurn(RED)
{
    if(N < 0){
        cerr << "Cannot have negative desired checkers!" << endl;
        exit(1);
    }
}

bool GameImpl::completed(int& winner) const
{
   
    return isDone(mScaffold, mN, winner);
}

bool GameImpl::takeTurn()
{
   
    int winner;
    if(completed(winner))
        return false;
    
    
    int col;
    if(mTurn == RED)
        col = mRed->chooseMove(mScaffold, mN, mTurn);
    else
        col = mBlack->chooseMove(mScaffold, mN, mTurn);
    
    //
    mScaffold.makeMove(col, mTurn);
    mTurn = opp(mTurn);
    return true;
}

void GameImpl::play()
{
    int winner;
    bool redInteractive   = mRed->isInteractive();
    bool blackInteractive = mBlack->isInteractive();

    // initial display
    mScaffold.display();

    // keep playing until completed()
    while (!completed(winner)) {
        takeTurn();
        mScaffold.display();

        // if neither player is interactive, pause after each move
        if (!redInteractive && !blackInteractive) {
            cout << "Press ENTER to continue...";
            // discard leftover input up to newline, then wait for ENTER
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    // announce the final result
    if (winner == RED)
        cout << mRed->name() << " Red wins!" << endl;
    else if (winner == BLACK)
        cout << mBlack->name() << " Black wins!" << endl;
    else
        cout << "Tie game." << endl;

}

int GameImpl::checkerAt(int c, int r) const
{
    return mScaffold.checkerAt(c,r);
}

//******************** Game functions **************************************

//  These functions simply delegate to GameImpl's functions.  You should not
//  change any of the code from here to the end of this file.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}


