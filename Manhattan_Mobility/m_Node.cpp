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
    mLocation.first = -1;
    mLocation.second = -1;
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
    mLocation.first = inLocation-> first;
    mLocation.second = inLocation-> second;
}

//set mLocation using parameters
void m_Node::setLocation(int xLocation, int yLocation)
{
    mLocation.first = xLocation;
    mLocation.second = yLocation;
}

pair<int,int> * m_Node::getLocation()
{
    return &mLocation;
}

//manage goal

//set goal using coord struct
void m_Node::setGoal(pair<int,int>* inGoal)
{
    goal.first = inGoal-> first;
    goal.second = inGoal-> second;
}

//set goal using parameters
void m_Node::setGoal(int xGoal, int yGoal)
{
    goal.first = xGoal;
    goal.second = yGoal;
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
