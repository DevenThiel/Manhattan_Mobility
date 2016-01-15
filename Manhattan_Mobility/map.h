/*************
*
*	Deven Thiel
*
*	06.15.2015
*
*	Map class outline for dynamic map of enviroment
*
*************/

#ifndef MAP_H
#define MAP_H

#include "dArray.h"

#include "coord.h"

template <class T>
class Map
{
	public:
		//default constructor
		Map ();
		
		//constructor with starting size
		Map (int, int);
		Map (coord *);
	
		//default destructor
		~Map();
	
		//map
		coord * getMapSize ();
		
		void addMapRow ();
		void addMapCol ();
		void delMapRow ();
		void delMapCol ();
	
		void shiftMapUp ();
		void shiftMapDown ();
		void shiftMapLeft ();
		void shiftMapRight ();
	
		void setNode (int, int, T *);
		void setNode (coord *, T *);
		T * getNode (int, int);
		T * getNode (coord *);
			
	private:
		void setMapSize (int, int);
		void setMapSize (coord *);
		
		DArray<DArray<T*> *> map;
		coord mapSize;
};

#include "map.t"

#endif