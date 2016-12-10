/*************
*
*	Deven Thiel
*
*	12.10.2016
*
*	Map class implimentation
*
*************/

#include "map.h"

//default constructor
template <class T>
Map<T>::Map ()
{
	mapSize.first = 0;
	mapSize.second = 0;
}

//constructor with starting size
template <class T>
Map<T>::Map (int x, int y)
{
	mapSize.first = x;
	mapSize.second = y;

	//add each column
	for (int i = 0; i < x; i++)
	{
		map.addElement();
		//add each row
		for (int j = 0; j < y; j++)
		{
			map[i].addElement();
		}
	}
}

template <class T>
Map<T>::Map (pair<int,int> * size)
{
	Map(size->first, size->second);
}

//default destructor
template <class T>
Map<T>::~Map()
{
	//deallocate all the memory assosiated with the map
	for (int i = (mapSize.first - 1); i >= 0; i--)
	{
		for (int j = (mapSize.second - 1); j >= 0; j--)
		{
			map[i]->deleteElement(j);
		}
		map.deleteElement(i);
	}
}

//maps
template<class T>
pair<int,int> * Map<T>::getMapSize ()
{
	pair<int,int> * temp;

	temp = & mapSize;

	return temp;
}

template <class T>
void Map<T>::addMapRow ()
{
	for (int i = 0; i < mapSize.first; i++)
	{
		map[i]->addElement();
	}

	mapSize.second ++;
}

template <class T>
void Map<T>::addMapCol()
{
	map.addElement();

	mapSize.first ++;
	for (int j = 0; j < mapSize.second; j ++)
	{
		map[mapSize.first - 1]->addElement();
	}
}

template <class T>
void Map<T>::delMapRow()
{
	for (int i = 0; i < mapSize.first; i++)
	{
		map[i]->deleteElement();
	}

	mapSize.second --;
}

template <class T>
void Map<T>::delMapCol()
{
	for (int j = 0; j < mapSize.second; j ++)
	{
		map[mapSize.first - 1]->deleteElement();
	}

	map.deleteElement();

	mapSize.first --;
}

template <class T>
void Map<T>::shiftMapUp()
{
	for (int i = 0; i < mapSize.first; i ++)
	{
		//delete anything in top row not 0
		if (map[i][mapSize.second - 1] != (T*)0)
		{
			delete map[i][mapSize.second - 1];
		}

		//move everything up a row
		for (int j = (mapSize.second - 1); j > 0; j--)
		{
			map[i][j] = map[i][j - 1];
		}

		//0 the bottom row
		map[i][0] = (T*)0;
	}
}

template <class T>
void Map<T>::shiftMapDown()
{
	for (int i = 0; i < mapSize.first; i ++)
	{
		//delete anything in bottom row not 0
		if (map[i][0] != (T*)0)
		{
			delete map[i][0];
		}

		//move everything up a row
		for (int j = 0; j < (mapSize.second - 1); j++)
		{
			map[i][j] = map[i][j + 1];
		}

		//0 the top row
		map[i][mapSize.second - 1] = (T*)0;
	}
}

template <class T>
void Map<T>::shiftMapLeft()
{
	for (int j = 0; j < mapSize.second; j ++)
	{
		//delete anything in left collumn not 0
		if (map[0][j] != (T*)0)
		{
			delete map[0][j];
		}

		//move everything left a collumn
		for (int i = 0; i < (mapSize.first - 1); i++)
		{
			map[i][j] = map[i + 1][j];
		}

		//0 the right collumn
		map[mapSize.first - 1][j] = (T*)0;
	}
}

template <class T>
void Map<T>::shiftMapRight()
{
	for (int j = 0; j < mapSize.second; j ++)
	{
		//delete anything in right collumn not 0
		if (map[mapSize.first - 1][j] != (T*)0)
		{
			delete map[mapSize.first - 1][j];
		}

		//move everything right a collumn
		for (int i = (mapSize.first - 1); i > 0; i--)
		{
			map[i][j] = map[i - 1][j];
		}

		//0 the left collumn
		map[0][j] = (T*)0;
	}
}

template <class T>
void Map<T>::setNode(int x, int y, T * theT)
{
	getNode(x,y) = theT;
}

template <class T>
void Map<T>::setNode(pair<int,int> * location, T * theT)
{
	setNode(location->first, location->second, theT);
}

template <class T>
T * Map<T>::getNode (int x, int y)
{
	if (x < mapSize.first && y < mapSize.second)
	{
		//return map[x][y];
		return getNode(x,y);
	}
	else
	{
		return (T*)0;
	}
}

template <class T>
T * Map<T>::getNode (pair<int,int> * location)
{
	return getNode(location->first, location->second);
}

template <class T>
void Map<T>::setMapSize (int x, int y)
{
	mapSize.first = x;
	mapSize.second = y;
}

template <class T>
void Map<T>::setMapSize (pair<int,int> * location)
{
	setMapSize(location->first, location->second);
}
