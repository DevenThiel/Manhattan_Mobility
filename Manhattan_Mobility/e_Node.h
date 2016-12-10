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
*	e_Node class which modles enviroment nodes of the simulation.
*	the e_node assosiated with each location on the map denotes its properties.
*
*************/

#ifndef E_NODE_H
#define E_NODE_H

//#include "coord.h" replaced with std::pair
#include <utility>
#include "m_Node.h"
//#include "dArray.h" replaced with std::vector
#include <vector>

using namespace std;

class e_Node
{
    public:
			//default constructor
			e_Node();

			//copy constructor
			e_Node(const e_Node & other);

			//default desructor
			~e_Node();

			//set gets for traversable permeable transmittable
			void setTraversable(bool inTraversable);
			void setPermeable(bool inPermeable);
			void setTransmittable(bool inTransmittable);
			bool isTraversable();
			bool isPermeable();
			bool isTransmittable();

			//manage location
			void setLocation(pair<int,int> *);
			void setLocation(int, int);
			pair<int,int> * getLocation();

			//manage range
			void setRange(float);
			float getRange();

			//manage landmark status
			void setLandmark(bool);
			bool isLandmark();

			//find m_Node in moblist
			int findMNode(int);

			//overload = operator
			e_Node& operator= (const e_Node & other);

			vector <m_Node*> moblist;

		private:
			//variable that determines if position on map can contain a mobile node
			bool traversable;

			//variable that determines if position on map can send transmissions across
			bool permeable;

			//variable that determines if position can send and recieve signals
			bool transmittable;

			//variable that determines landmark status
			bool landmark;

			pair<int,int> eLocation;

			float eRange;
};

#endif
