/*************
*
*	Arban Nichols
*
*	06.15.2015
*
*	Deven Thiel
*
*	12.10.2016
*
*	m_Node implementation file
*
*************/

#include "m_Node.h"

//default constructor
m_Node::m_Node()
{
    mLocation.x = -1;
    mLocation.y = -1;
    mRange = 0.0;
}

//copy constructor
m_Node::m_Node(const m_Node & other )
{
    mLocation = other.mLocation;
    mId = other.mId;
    mRange = other.mRange;
    goal = other.goal;
}

//manage position

//set mLocation using coord struct
void m_Node::setLocation(pair<int,int>* inLocation)
{
    mLocation.x = inLocation-> x;
    mLocation.y = inLocation-> y;
}

//set mLocation using parameters
void m_Node::setLocation(int xLocation, int yLocation)
{
    mLocation.x = xLocation;
    mLocation.y = yLocation;
}

pair<int,int> * m_Node::getLocation()
{
    return &mLocation;
}

//manage goal

//set goal using coord struct
void m_Node::setGoal(pair<int,int>* inGoal)
{
    goal.x = inGoal-> x;
    goal.y = inGoal-> y;
}

//set goal using parameters
void m_Node::setGoal(int xGoal, int yGoal)
{
    goal.x = xGoal;
    goal.y = yGoal;
}

pair<int,int> * m_Node::getGoal()
{
    return &goal;
}


//manage id number

//set id
void m_Node::setId (int num)
{
    mId = num;
}

int m_Node::getId()
{
    return mId;
}

//manage range value
void m_Node::setRange (float inRange)
{
    mRange = inRange;
}

float m_Node::getRange()
{
    return mRange;
}

//overload = operator
m_Node & m_Node::operator= (const m_Node & other)
{
    mLocation = other.mLocation;
    mId = other.mId;
    mRange = other.mRange;
    goal = other.goal;

    return *this;
}
