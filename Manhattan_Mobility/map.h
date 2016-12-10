/*************
*
*	Deven Thiel
*
*	12.10.2016
*
*	Map class outline for dynamic map of enviroment
*
*************/

#ifndef MAP_H
#define MAP_H

//#include "dArray.h" replaced with std::vector
#include <vector>
//#include "coord.h" replaced with std::pair
#include <utility>

using namespace std;

template <class T>
class Map
{
	public:
		//default constructor
		Map ();

		//constructor with starting size
		Map (int, int);
		Map (pair<int,int> *);

		//default destructor
		~Map();

		//map
		pair<int,int> * getMapSize ();

		void addMapRow ();
		void addMapCol ();
		void delMapRow ();
		void delMapCol ();

		void shiftMapUp ();
		void shiftMapDown ();
		void shiftMapLeft ();
		void shiftMapRight ();

		void setNode (int, int, T *);
		void setNode (pair<int,int> *, T *);
		T * getNode (int, int);
		T * getNode (pair<int,int> *);

	private:
		void setMapSize (int, int);
		void setMapSize (pair<int,int> *);

		vector<vector<T*> *> map;
		pair<int,int> mapSize;
};

#include "map.t"

#endif
