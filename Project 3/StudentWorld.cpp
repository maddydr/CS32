#include "StudentWorld.h"
#include "GameConstants.h"
#include "Board.h"
#include <string>

#include "Actor.h"
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_bd = nullptr;
}

int StudentWorld::init()
{
    // call asset path?
    // use board class and load the board data file
    m_bd = new Board;
    string board_file = assetPath() + "board0" + std::to_string(getBoardNumber()) + ".txt";
    cout << board_file << endl;
    Board::LoadResult result = m_bd->loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
    {
        cerr << "Could not be found from";
        return GWSTATUS_BOARD_ERROR;
    }
    else if (result == Board::load_fail_bad_format)
    {
        cerr << "Your board was improperly formatted \n";
        return GWSTATUS_BOARD_ERROR;
    }
    else if (result == Board::load_success)
        cerr << "successfully located the board";
    
    
    playerAvatar* peach;
    //playerAvatar* yoshi;
    int startX = 0;
    int startY = 0;
    // the boardtxt is a 16x16 grid (coords 0-15)
    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            Board::GridEntry ge = m_bd->getContentsOf(i, k);
            switch (ge)
            {
                case Board::empty:
                    break;
                case Board::player:
                {
                    startY = i;
                    startX = k;
                    peach = new playerAvatar(IID_PEACH, SPRITE_HEIGHT*startY, SPRITE_WIDTH*startX, 0, 0,this);
                    m_actorPtrs.push_back(peach);
                    m_actorPtrs.push_back(new square(IID_BLUE_COIN_SQUARE, SPRITE_HEIGHT*i, SPRITE_WIDTH*k,0,1,this, peach));
                    break;
                }
                case Board::blue_coin_square:
                {
                    Actor* blue = new square(IID_BLUE_COIN_SQUARE, SPRITE_HEIGHT*i, SPRITE_WIDTH*k,0,1,this, peach);
                    m_actorPtrs.push_back(blue);
                    break;
                }
                case Board::red_coin_square:
                    break;
                case Board::up_dir_square:
                    break;
                case Board::down_dir_square:
                    break;
                case Board::left_dir_square:
                    break;
                case Board::right_dir_square:
                    break;
                case Board::event_square:
                    break;
                case Board::bank_square:
                    break;
                case Board::star_square:
                    break;
                case Board::bowser:
                {
//                    Actor* bowser = new Avatar(IID_BOWSER, SPRITE_HEIGHT*i, SPRITE_WIDTH*k, 0, 0);
//                    m_actorPtrs.push_back(bowser);
                    break;
                }
                case Board::boo:
                    break;
            }
                
        }
    }
//    Actor* yoshi = new playerAvatar(IID_YOSHI, SPRITE_HEIGHT*startY, SPRITE_WIDTH*startX, 0, 0);
//    m_actorPtrs.push_back(yoshi);
    
    
//
//    1. Initialize the data structures used to keep track of your game’s world.
//    2. Allocate and insert Peach and Yoshi objects into the game world. Every time a
//    game begins, Peach and Yoshi start out initialized in their starting location as
//    specified by the current board data file.
//    3. Allocate and insert all of the other objects (e.g., squares, baddies, etc.) into the
//    game world as described below.
//    4. Start the countdown timer for the 99-second game.
//
    
    
	startCountdownTimer(99999);  // this placeholder causes timeout after 5 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    
    // iterate through vector asking each one to do something
    for (int i = 0; i < m_actorPtrs.size(); i++)
    {
        m_actorPtrs[i]->doSomething();
    }

    setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0)
		return GWSTATUS_NOT_IMPLEMENTED;
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < m_actorPtrs.size(); i++)
    {
        delete m_actorPtrs[i];
        m_actorPtrs[i] = nullptr;
    }
   
    if (m_bd != nullptr)
    {
        delete m_bd;
        m_bd = nullptr;
    }
}


Board* StudentWorld::boardPtr() // returns the pointer to the new board we allocated
{
    return m_bd;
}
// make a function that returns a pointer to the BOARD


StudentWorld::~StudentWorld()
{
    cleanUp();
}
