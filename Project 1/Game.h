//
//  Game.hpp
//  cs32 p1
//
//  Created by Maddy Delos Reyes on 1/14/23.
//

#include <string>
#ifndef Game_h
#define Game_h

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_h */
