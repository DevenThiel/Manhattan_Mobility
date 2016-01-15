#ifndef E_NODE_H
#define E_NODE_H

#include "coord.h"
#include "m_Node.h"
#include "dArray.h"


	
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
        void setLocation(coord *);
        void setLocation(int, int);
        coord * getLocation();
        
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
	
		DArray<m_Node*> moblist;
        
     private:
        //variable that determines if position on map can contain a mobile node
        bool traversable;
        
    	//variable that determines if position on map can send transmissions across
    	bool permeable;
    	
    	//variable that determines if position can send and recieve signals
    	bool transmittable;
        
        //variable that determines landmark status
        bool landmark;
     
        coord eLocation;
        
        float eRange;
};

#endif