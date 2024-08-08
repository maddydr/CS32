#include "Actor.h"
#include "StudentWorld.h"



// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp



Actor::Actor(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr) // actor constructor
:GraphObject(ID, startX, startY, startDir, depth, 1.0)
{
    m_SWptr = ptr;
}

StudentWorld* Actor::getWorld()
{
    return m_SWptr;
}
//void Actor::doSomething() = 0; // PURE VIRTUAL BECAUSE CANNOT MAKE A 'ACTOR' TYPE
    

    
    





//    1. A Player Avatar object must have an image ID of IID_PEACH or IID_YOSHI.
//    2. A Player Avatar object has a sprite direction of 0 degrees.
//    3. A Player Avatar object has a starting walk direction of right.
//    4. A Player Avatar object has a starting (x,y) position based on the board data file.
//    Your StudentWorld object can pass in that position when constructing this object.
//    5. A Player Avatar must keep track of whether it is player 1 (uses left side of
//    keyboard) or player 2 (uses right side of keyboard).
//    6. A Player Avatar object has a graphical depth of 0.
//    7. A Player Avatar object has a size of 1.
//    8. A Player Avatar object starts with zero coins and zero stars.
//    9. A Player Avatar object starts with no Vortex projectile.
//    10. A Player Avatar has a ticks_to_move value of 0.
//    11. A Player Avatar starts out in the waiting to roll state.
Avatar::Avatar(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr) // avatars include baddies and yoshi and peach
:Actor(ID, startX, startY, startDir, depth, ptr)
{
    m_walkDir = 0; // every avatar should have initial walking direction of right
}

int Avatar::getWalkDir()
{
    return m_walkDir;
}

void Avatar::setWalkDir(int dir)
{
    m_walkDir = dir;
}


    
    

    

// player avatars are only yoshi and peaches
playerAvatar::playerAvatar(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr)
:Avatar(ID, startX, startY, startDir, depth, ptr)
{
    waitingToRoll = true; // false means it is WAITING to roll
    
    if (ID == 0) // means its a peach
        isRight = false; // right handed side analogous for false
    else
        isRight = true;
    
    spriteDir = 0; // are sprite Dir and startDir the same thing?
    coins = 0;
    stars = 0;
    vortex = false;
    ticks_to_move = 0;
}

void playerAvatar::doSomething()
{
    if (waitingToRoll == true) //player is waiting to roll
        // see if the user pressed something with getAction()
    {
        switch(getWorld()->getAction(1))
        {
            case(ACTION_ROLL):
            {
                int die_roll = randInt(1, 10); // IS THIS INCLUSIVE ???
                ticks_to_move = die_roll*8;
                waitingToRoll = false; // player is now walking
                
                break; // break ?????????????
            }
            case(ACTION_NONE):
            {
                return;
            }
        }
    }
    
    
    if (waitingToRoll == false) // if player avatar is in a walking state
    {

        int newX;
        int newY;
        
        int logic = 0;
        
        // FIGURE OUT WHAT DIRECTION WALKING
        // IS THIS NEXT MOVE VALID
        
        int dir = getWalkDir();
      // need to check if next move is empty

        getPositionInThisDirection(dir, SPRITE_WIDTH, newX, newY);
        
        if (newX % 16 == 0 && newY % 16 == 0) // only want to check if next entire move is valid, not just every little chunk
        {
            Board::GridEntry newge = getWorld()->boardPtr()->getContentsOf(newX/16, newY/16); // checks validity of hypothetical next pos
            if (newge == Board::empty) // can't move
                logic = -1;
        }
        
        
        
        if (logic != 0) // this means in some direction, the avatar can't move
        {
            // current direction is up, try to move right, then left
            //current direction is down, try to move right, then left
            // current direction is left, try to move up, then down
            // current direction is right, try to move up, then down
            switch (dir)
            {
                case(down):
                case(up):
                {
                    getPositionInThisDirection(right, SPRITE_WIDTH, newX, newY);
                    Board::GridEntry newge = getWorld()->boardPtr()->getContentsOf(newX/16, newY/16); // checking is this next move valid?
                    if (newge != Board::empty) // yes next move is valid
                    {
                        setDirection(right); // only changes the direction the sprite is facing
                        setWalkDir(right); // now we want it to move right
                    }
                    else // this means can't move right
                    {   
                        setDirection(left);
                        setWalkDir(left);
                    }
                    break;
                }
                case(right):
                case(left):
                {
                    setDirection(right);
                    getPositionInThisDirection(up, SPRITE_WIDTH, newX, newY);
                    Board::GridEntry newge = getWorld()->boardPtr()->getContentsOf(newX/16, newY/16);
                    if (newge != Board::empty)
                    {
                        setWalkDir(up);
                    }
                    else
                    {
                        setWalkDir(down);
                    }
                    break;
                }
                    
            }
        }

        moveAtAngle(getWalkDir(), 2);
      //  moveTo(newX, newY);
        ticks_to_move--;
        if (ticks_to_move <= 0)
            waitingToRoll = true;

    }  
    
    return;
}
    





square::square(int ID, int startX, int startY, int startDir, int depth, StudentWorld* world, playerAvatar* playerPtr)
:Actor(ID, startX, startY, startDir, depth, world)
{
    alive = true;
}
void square::doSomething()
{
    if (alive == false) // square is not active, return
        return;
    
    // is player on the square? --- if yes, increment its coin counter +3
    
    
}


