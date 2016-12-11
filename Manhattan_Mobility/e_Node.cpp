/*************
*
*	Arban Nichols
*
*	06.15.2015
*
*	Deven Thiel
*
*	12.11.2016
*
*	e_Node class implementation file
*
*************/

#include "e_Node.h"

//default constructor
e_Node::e_Node()
{
    traversable = false;
    transmittable = false;
    permeable = false;
    landmark = false;

    eRange = 0.0;
}

//copy constructor
e_Node::e_Node(const e_Node & other )
{
    traversable = other.traversable;
    transmittable = other.transmittable;
    permeable = other.permeable;
    landmark = other.landmark;

    moblist = other.moblist;

    eLocation = other.eLocation;

    eRange = other.eRange;
}

//destructor
e_Node::~e_Node()
{

}

//set coordinate location using coord struct
void e_Node::setLocation(pair<int,int>* inLocation)
{
    eLocation.first = inLocation-> first;
    eLocation.second = inLocation-> second;
}

//set coordinate location using parameters
void e_Node::setLocation(int xLocation, int yLocation)
{
    eLocation.first = xLocation;
    eLocation.second = yLocation;
}

pair<int,int>* e_Node::getLocation()
{
    return &eLocation;
}

//set traversability
void e_Node::setTraversable(bool inTraversable)
{
    traversable = inTraversable;
}

//set transmittabilty
void e_Node::setTransmittable(bool inTransmittable)
{
    transmittable = inTransmittable;
}

//set permeability
void e_Node::setPermeable(bool inPermeable)
{
    permeable = inPermeable;
}

//gets for permeable traversable and transmittable
bool e_Node::isTraversable()
{
    return traversable;
}

bool e_Node::isTransmittable()
{
    return transmittable;
}

bool e_Node::isPermeable()
{
    return permeable;
}

//manage range value
void e_Node::setRange(float inRange)
{
    eRange = inRange;
}

float e_Node::getRange()
{
    return eRange;
}

//manage landmark status
void e_Node::setLandmark(bool inLandmark)
{
    landmark = inLandmark;
}

bool e_Node::isLandmark()
{
    return landmark;
}

//find m_Node in moblist
int e_Node::findMNode(int search)
{
    int l = moblist.size();

    for(int i=0; i < moblist.size(); i++)
    {
        if (moblist[i]->getId() == search)
        return i;
    }

    return -1;
}

//overload = operator
e_Node & e_Node::operator= (const e_Node & other)
{
    traversable = other.traversable;
    transmittable = other.transmittable;
    permeable = other.permeable;
    landmark = other.landmark;

    moblist = other.moblist;

    eLocation = other.eLocation;

    eRange = other.eRange;

    return *this;
}
