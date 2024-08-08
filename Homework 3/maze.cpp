//
//  main.cpp
//  hw3 maze
//
//  Created by Maddy Delos Reyes on 2/14/23.
//


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    else
    {
        maze[sr][sc] = '*';
        
        if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) // NORTH
        {
            maze[sr - 1][sc] = '*';
            return true;
        }
        
        if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) // EAST
        {
            maze[sr][sc + 1] = '*';
            return true;
        }
        
        if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) // SOUTH
        {
            maze[sr + 1][sc] = '*';
            return true;
        }
        
        if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) // WEST
        {
            maze[sr][sc - 1] = '*';
            return true;
        }
        
    }
    
    return false;
}





