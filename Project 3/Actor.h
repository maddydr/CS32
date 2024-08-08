#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// why was #include "studentWorld" causing errors?

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp


class Actor : public GraphObject // BASE CLASS
{
public:
    Actor(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr);
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    
private:
    StudentWorld* m_SWptr;
    
};





class Avatar : public Actor
{
public:
    Avatar(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr);
    bool internalState();
    virtual void doSomething() = 0; // every baddie, and playeravatar does something different on each tick
    int getWalkDir();
    void setWalkDir(int dir);
    
private:
    int m_walkDir;
    bool walking;
};





class playerAvatar: public Avatar
{
public:
    playerAvatar(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr);
    virtual void doSomething();
    
private:
    bool isRight;
    bool waitingToRoll;
    int spriteDir;
    int coins;
    int stars;
    bool vortex;
    int ticks_to_move;
};




class square: public Actor
{
public:
    square(int ID, int startX, int startY, int startDir, int depth, StudentWorld* ptr, playerAvatar* playerPtr);
    virtual void doSomething();
private:
    bool alive;
};
#endif // ACTOR_H_
