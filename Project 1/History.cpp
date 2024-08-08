
#include "globals.h"
#include "History.h"
#include <iostream>

using namespace std;


History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for (int i = 0; i < m_rows; i++) // initalize all counter's in array to 0
    {
        for (int k = 0; k < m_cols; k++)
            historyArray[i][k] = 0;
    }
}


bool History::record (int r, int c)
{
    if (r > m_rows || c > m_cols)
        return false;
    
    
    historyArray[r - 1][c - 1]++;
    
    
    return true;
}


void History::display() const
{
    clearScreen();
    
    for (int i = 0; i < m_rows; i++)
    {
        for (int k = 0; k < m_cols; k++)
        {
            if (historyArray[i][k] == 0)
                cout << ".";
            else if (historyArray[i][k] >= 26)
                cout << 'Z';
            else
            {
                char alpha = historyArray[i][k] + 64;
                cout << alpha;
            }
        }
        cout << endl;
    }
    cout << endl;
}
