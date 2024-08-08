////
////  mazequeue.cpp
////  CS32HW2
////
////  Created by Maddy Delos Reyes on 2/7/23.
////
//
//#include <queue>
//#include <iostream>
//#include <string>
//using namespace std;
//
//
//
//class Coord
//{
//  public:
//    Coord(int r, int c) : m_row(r), m_col(c) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//  private:
//    int m_row;
//    int m_col;
//};
//
//
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
//{
//    queue<Coord> coordQueue;
//    coordQueue.push(Coord(sr,sc)); // pushes the start coordinates of a type Coord which itself contains a row and column number
//    maze[sr][sc] = '*';
//    while (!coordQueue.empty())
//    {
//        Coord current = coordQueue.front(); // changed from 'top' to queues 'front' to view active item
//        int r = current.r(); // current row position
//        int c = current.c(); // current column position
//        coordQueue.pop(); // removes the top of the Queue item
//        if (r == er && c == ec) // found the end of the maze
//            return true;
//        //east
//        if((c + 1) < nCols && maze[r][c+1] != '*' && maze[r][c+1] != 'X')
//        {
//            coordQueue.push(Coord(r,c+1));
//            maze[r][c+1] = '*';
//        }
//
//        //north
//        if((r - 1) >= 0 && maze[r-1][c] != '*' && maze[r-1][c] != 'X')
//        {
//            coordQueue.push(Coord(r-1,c));
//            maze[r-1][c] = '*';
//        }
//
//        // west
//        if((c - 1) >= 0 && maze[r][c-1] != '*' && maze[r][c-1] != 'X')
//        {
//            coordQueue.push(Coord(r,c-1));
//            maze[r][c-1] = '*';
//        }
//
//        //south
//        if((r+1) < nRows && maze[r+1][c] != '*' && maze[r+1][c] != 'X')
//        {
//            coordQueue.push(Coord(r+1,c));
//            maze[r+1][c] = '*';
//        }
//    }
//
//    return false;
//}
//
//int main()
//{
//
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X..X...X.X",
//        "X.XXXX.X.X",
//        "X.X.X..X.X",
//        "X...X.XX.X",
//        "XXX......X",
//        "X.X.XXXX.X",
//        "X.XXX....X",
//        "X...X..X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 5,3, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//
//
//}
