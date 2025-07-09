// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <stack>
#include <iostream>
#include <utility>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
private:
    int m_cols, m_levels;
    vector<vector<int>> grid;
    stack<pair<int, int>> moveHistory;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels): m_cols(nColumns), m_levels(nLevels)
{
    if(nColumns <= 0  || nLevels <= 0) {
        cerr << "invalid dimensions" << endl;
        exit(1);
    }
    grid = vector<vector<int>>(m_cols, vector<int>(m_levels, VACANT));
}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    int count = 0;
    for(int i = 0; i < m_cols; i++) {
        for(int j = 0; j < m_levels; j++) {
            if(grid[i][j] == VACANT) {
                count++;
            }
        }
        
    }
    return count;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column < 1 || column > m_cols || level < 1 || level > m_levels)
            return VACANT; // the level or column is invalid
    return grid[column - 1][level - 1];
}

void ScaffoldImpl::display() const
{
    for (int lvl = m_levels - 1; lvl >= 0; --lvl) {
        cout << "|";
        for (int col = 0; col < m_cols; ++col) {
            char ch;
            if (grid[col][lvl] == RED)
                ch = 'R';
            else if (grid[col][lvl] == BLACK)
                ch = 'B';
            else
                ch = ' ';
            cout << ch << "|";
        }
        cout << endl;
    }
    for (int i = 0; i < m_cols; ++i)
        cout << "+-";
    cout << "+" << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column < 1 || column > m_cols || (color != RED && color != BLACK))
            return false;

        int colIndex = column - 1;
    
    for (int lvl = 0; lvl < m_levels; ++lvl) {
           if (grid[colIndex][lvl] == VACANT) {
               grid[colIndex][lvl] = color;
               moveHistory.push({colIndex, lvl}); // this means that the column is full
               return true;
           }
       }
       return false;
}

int ScaffoldImpl::undoMove()
{
    if (moveHistory.empty())
            return 0;
    pair<int, int> lastMove = moveHistory.top();
    moveHistory.pop();
    grid[lastMove.first][lastMove.second] = VACANT;
    return lastMove.first + 1;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.  You should
//  not change any of the code from here to the end of this file.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}


