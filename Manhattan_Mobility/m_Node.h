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
*	m_Node class which modles mobile nodes of the simulation.
*	each m_node exists in a single location within the map at any time for which there also exists an e_node definition.
* m_node modles the characteristics and states of each mobile node.
*
*************/

#ifndef M_NODE_H
#define M_NODE_H

//#include "coord.h" replaced with std::pair
#include <utility>
//#include "dArray.h" replaced with std::vector
#include <vector>

using namespace std;

class m_Node
{
 	public:
		//default constructor
		m_Node();

		//default destructor
		~m_Node();

		//copy constructor
		m_Node(const m_Node & other);

		//manage position
		void setLocation (pair<int,int>*);
		void setLocation (int, int);
		pair<int,int> * getLocation();

		// manage destination
		void setGoal (pair<int,int>*);
		void setGoal (int, int);
		pair<int,int> * getGoal();

		//manage id number
		void setId (int);
		int getId();

		//manage transmission range
		void setRange (float);
		float getRange();

		//overload = operator
		m_Node & operator= (const m_Node & other);

		//public data

		vector <pair<int,int> *> path;

	private:

		pair<int,int> mLocation;

		pair<int,int> goal;

		int mId;

		float mRange;
};

#endif
