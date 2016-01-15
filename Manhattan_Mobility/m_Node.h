#ifndef M_NODE_H
#define M_NODE_H

#include "coord.h"
#include "dArray.h"

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
		void setLocation (coord*);
		void setLocation (int, int);
		coord * getLocation();

		// manage destination
		void setGoal (coord*);
		void setGoal (int, int);
		coord * getGoal();

		//manage id number
		void setId (int);
		int getId();
		
		//manage transmission range
		void setRange (float);
		float getRange();
		
		//overload = operator
		m_Node & operator= (const m_Node & other);
	
		//public data
	
		DArray <coord *> path;

	private:
		
		coord mLocation;
		
		coord goal;
		
		int mId;
		
		float mRange;
};

#endif
