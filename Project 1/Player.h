//
//  player.hpp
//  cs32 p1
//
//  Created by Maddy Delos Reyes on 1/14/23.
//
#include <string>
#ifndef Player_h
#define Player_h


class Arena;
class History;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    std::string dropPoisonedCarrot();
    std::string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
    
};

#endif /* player_h */
