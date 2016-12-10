/*************
*
*	Deven Thiel
*
*	06.15.2015
*
*	Map class implimentation
*
*************/

#include "map.h"

//default constructor
template <class T>
Map<T>::Map ()
{
	mapSize.x = 0;
	mapSize.y = 0;
}

//constructor with starting size
template <class T>
Map<T>::Map (int x, int y)
{
	mapSize.x = x;
	mapSize.y = y;

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
Map<T>::Map (coord * size)
{
	Map(size->x, size->y);
}

//default destructor
template <class T>
Map<T>::~Map()
{
	//deallocate all the memory assosiated with the map
	for (int i = (mapSize.x - 1); i >= 0; i--)
	{
		for (int j = (mapSize.y - 1); j >= 0; j--)
		{
			map[i]->deleteElement(j);
		}
		map.deleteElement(i);
	}
}

//maps
template<class T>
coord * Map<T>::getMapSize ()
{
	coord * temp;

	temp = & mapSize;

	return temp;
}

template <class T>
void Map<T>::addMapRow ()
{
	for (int i = 0; i < mapSize.x; i++)
	{
		map[i]->addElement();
	}

	mapSize.y ++;
}

template <class T>
void Map<T>::addMapCol()
{
	map.addElement();

	mapSize.x ++;
	for (int j = 0; j < mapSize.y; j ++)
	{
		map[mapSize.x - 1]->addElement();
	}
}

template <class T>
void Map<T>::delMapRow()
{
	for (int i = 0; i < mapSize.x; i++)
	{
		map[i]->deleteElement();
	}

	mapSize.y --;
}

template <class T>
void Map<T>::delMapCol()
{
	for (int j = 0; j < mapSize.y; j ++)
	{
		map[mapSize.x - 1]->deleteElement();
	}

	map.deleteElement();

	mapSize.x --;
}

template <class T>
void Map<T>::shiftMapUp()
{
	for (int i = 0; i < mapSize.x; i ++)
	{
		//delete anything in top row not 0
		if (map[i][mapSize.y - 1] != (T*)0)
		{
			delete map[i][mapSize.y - 1];
		}

		//move everything up a row
		for (int j = (mapSize.y - 1); j > 0; j--)
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
	for (int i = 0; i < mapSize.x; i ++)
	{
		//delete anything in bottom row not 0
		if (map[i][0] != (T*)0)
		{
			delete map[i][0];
		}

		//move everything up a row
		for (int j = 0; j < (mapSize.y - 1); j++)
		{
			map[i][j] = map[i][j + 1];
		}

		//0 the top row
		map[i][mapSize.y - 1] = (T*)0;
	}
}

template <class T>
void Map<T>::shiftMapLeft()
{
	for (int j = 0; j < mapSize.y; j ++)
	{
		//delete anything in left collumn not 0
		if (map[0][j] != (T*)0)
		{
			delete map[0][j];
		}

		//move everything left a collumn
		for (int i = 0; i < (mapSize.x - 1); i++)
		{
			map[i][j] = map[i + 1][j];
		}

		//0 the right collumn
		map[mapSize.x - 1][j] = (T*)0;
	}
}

template <class T>
void Map<T>::shiftMapRight()
{
	for (int j = 0; j < mapSize.y; j ++)
	{
		//delete anything in right collumn not 0
		if (map[mapSize.x - 1][j] != (T*)0)
		{
			delete map[mapSize.x - 1][j];
		}

		//move everything right a collumn
		for (int i = (mapSize.x - 1); i > 0; i--)
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
void Map<T>::setNode(coord * location, T * theT)
{
	setNode(location->x, location->y, theT);
}

template <class T>
T * Map<T>::getNode (int x, int y)
{
	if (x < mapSize.x && y < mapSize.y)
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
T * Map<T>::getNode (coord * location)
{
	return getNode(location->x, location->y);
}

template <class T>
void Map<T>::setMapSize (int x, int y)
{
	mapSize.x = x;
	mapSize.y = y;
}

template <class T>
void Map<T>::setMapSize (coord * location)
{
	setMapSize(location->x, location->y);
}
