/*************
*
*	Deven Thiel
*
*	12.11.2016
*
*	dispatcher implementation for manhattan mobility model
*
*************/

#include "dispatcher.h"

#include <cmath>
#include <ctime>

Dispatcher::Dispatcher()
{
	currentTime = 0;
}

Dispatcher::~Dispatcher()
{
	//close file if needed
	out->close();
}

//inline function for pointer to NULL check
inline bool ckTraversable (e_Node * inNode)
{
	if (inNode == 0)
	return false;
	else
	return inNode->isTraversable();
}

//pathfinder
void Dispatcher::pathfinder (m_Node * mobnode)
{
	//pointer for each relivant enode
	e_Node * fpos, * fneg, * spos, * sneg, * loc;
	//traversability
	bool tfpos, tfneg, tspos, tsneg;
	//pairs of all relivant locations for this m_node
	pair<int,int> * start, * current, * finish;

	start = mobnode->getLocation();
	finish = mobnode->getGoal();
	current = start;

	//until path is found to finish
	while (!(current->first == finish->first && current->second == finish->second))
	{

		//get enode mnode is currently in
		loc = getEnode(start);
		//fill e_node pointers
		fpos = getEnode(current->first+1,current->second);
		fneg = getEnode(current->first-1,current->second);
		spos = getEnode(current->first,current->second+1);
		sneg = getEnode(current->first,current->second-1);
		//fill traversability
		if (fpos != 0)
		{
			tfpos = fpos->isTraversable();
		}
		else
		{
			tfpos = false;
		}
		if (fneg != 0)
		{
			tfneg = fneg->isTraversable();
		}
		else
		{
			tfneg = false;
		}
		if (spos != 0)
		{
			tspos = spos->isTraversable();
		}
		else
		{
			tspos = false;
		}
		if (sneg != 0)
		{
			tsneg = sneg->isTraversable();
		}
		else
		{
			tsneg = false;
		}

		//find most desirable direction
		int f = finish->first - current->first;
		int s = finish->second - current->second;

		//prefer to move in direction closest to 0 distance
		//move in direction furthest from 0 distance
		//move away from direction furthest from 0
		//move away from direction closest to 0

		if (abs(f) <= abs(s) && f != 0)//prefer f
		{
			if (f > 0 && s > 0)//f pos s pos
			{
				//fpos 0x0
				if (tfpos)
				{
					current->first ++;
				}
				else if (tspos)
				{
					current->second ++;
				}
				else if (tsneg)
				{
					current->second --;
				}
				else if (tfneg)
				{
					current->first --;
				}
			}
			else if (f < 0 && s > 0)//f neg s pos
			{
				if (tfneg)
				{
					current->first --;
				}
				else if (tspos)
				{
					current->second ++;
				}
				else if (tsneg)
				{
					current->second --;
				}
				else if (tfpos)
				{
					current->first ++;
				}
			}
			else if (f > 0 && s < 0)//f pos s neg
			{
				if (tfpos)
				{
					current->first ++;
				}
				else if (tsneg)
				{
					current->second --;
				}
				else if (tspos)
				{
					current->second ++;
				}
				else if (tfneg)
				{
					current->first --;
				}
			}
			else if (f < 0 && s < 0)//f neg s neg
			{
				if (tfneg)
				{
					current->first --;
				}
				else if (tsneg)
				{
					current->second --;
				}
				else if (tspos)
				{
					current->second ++;
				}
				else if (tfpos)
				{
					current->first ++;
				}
			}
		}
		else//prefer s
		{
			if (s > 0 && f > 0)//s pos f pos
			{
				if (tspos)
				{
					current->second ++;
				}
				else if (tfpos)
				{
					current->first ++;
				}
				else if (tfneg)
				{
					current->first --;
				}
				else if (tsneg)
				{
					current->second --;
				}
			}
			else if (s < 0 && f > 0)//s neg f pos
			{
				if (tsneg)
				{
					current->second --;
				}
				else if (tfpos)
				{
					current->first ++;
				}
				else if (tfneg)
				{
					current->first --;
				}
				else if (tspos)
				{
					current->second ++;
				}
			}
			else if (s > 0 && f < 0)//s pos f neg
			{
				if (tspos)
				{
					current->second ++;
				}
				else if (tfneg)
				{
					current->first --;
				}
				else if (tfpos)
				{
					current->first ++;
				}
				else if (tsneg)
				{
					current->second --;
				}
			}
			else if (s < 0 && f < 0)//s neg f neg
			{
				if (tsneg)
				{
					current->second --;
				}
				else if (tfneg)
				{
					current->first --;
				}
				else if (tfpos)
				{
					current->first ++;
				}
				else if (tspos)
				{
					current->second ++;
				}
			}
		}

		mobnode->path.push_back(current);
	}
}

//trip planner
pair<int,int> * Dispatcher::tripPlanner ()
{
	pair<int,int> * goal;
	e_Node * destination;
	int r = rand() % traversableENodes.size();
	cout << "r:" << r << " - ";
	destination = traversableENodes.at(r);
	goal = destination->getLocation();
	cout << "rand:" << goal->first << "," << goal->second << endl;
	return goal;
}

//move
void Dispatcher::move (m_Node * mobnode)
{
	e_Node * tempE;
	m_Node * tempM;

	//if no path
	while (mobnode->path.size() == 0)
	{
		//trip planner
		mobnode->setGoal(tripPlanner());
		//path finder
		pathfinder(mobnode);
	}

	//get enode holding mnode
	tempE = getEnode(mobnode->getLocation());
	//remove mnode from enode
	if (tempE->findMNode(mobnode->getId()) == -1)
	{
		cout << "not found";
	}
	else
	{
		tempE->moblist.erase(tempE->moblist.begin() + tempE->findMNode(mobnode->getId()));
	}
	//update m_node location
	//vector pop, should this be changed to a queue?
	mobnode->setLocation(mobnode->path.front());
	mobnode->path.erase(mobnode->path.begin());
	//find enode to hold mnode
	tempE = getEnode(mobnode->getLocation());
	//add mnode to enode
	tempE->moblist.push_back(mobnode);
}

//map builder
void Dispatcher::buildMap (pair<int,int> size, pair<int,int> type)
{
	e_Node * theENode;
	e_Node * tempE;
	//grow map
	for (int x = 0; x < size.first; x++)
	{
		theMap.addMapCol();
	}

	for (int y = 0; y < size.second; y++)
	{
		theMap.addMapRow();
	}

	//consider type defined
	int tx = (int)(size.first / type.first);
	int ty = (int)(size.second / type.second);

	for (int x = 0; x < size.first; x++)
	{
		for (int y = 0; y < size.second; y++)
		{
			//add to e_Node list
			theENode = new e_Node;
			theENode->setPermeable(false);
			theENode->setTransmittable(false);
			theENode->setLocation(x,y);

			if (x % tx == 0 || y % ty == 0)
			{
				//traversible

				theENode->setTraversable(true);

				//add traversable list
				traversableENodes.push_back(theENode);
			}
			else
			{
				theENode->setTraversable(false);
			}

			//add to eNodes
			eNodes.push_back(theENode);

			//add to map
			theMap.setNode(x,y,theENode);
			if (theMap.getNode(x,y) == 0)
			{
				cout << "null e-node at" << x << "," << y << endl;
			}
		}
	}
}

//m_Node builder
void Dispatcher::buildm_Node (int num)
{
	m_Node * anMNode;
	m_Node * tempM;

	for (int z = 0; z < num; z++)
	{
		anMNode = new m_Node;
		anMNode->setLocation(tripPlanner());
		anMNode->setId(z);

		mNodes.push_back(anMNode);

	}
}

//display
void Dispatcher::displayMap ()
{
	pair<int,int> * size = theMap.getMapSize();
	e_Node * theNode;

	for (int j = (size->second - 1); j >= 0; j--)
	{
		cout << "+";
		for (int i = 0; i < size->first; i++)
		{
			cout << "-+";
		}
		cout << endl;
		cout << "|";
		for (int i = 0; i < size->first; i++)
		{
			theNode = theMap.getNode(i,j);
			if (theNode == NULL)
			{
				cout << "-";
			}
			else if (theNode->isTraversable() == true)
			{
				cout << "O";
			}
			else
			{
				cout << "X";
			}
			cout << "|";
		}
		cout << endl;
	}
}

//data file
void Dispatcher::printData ()
{
	m_Node * theNode;

	*out << "t:" << currentTime << endl;

	for (int i = 0; i < mNodes.size(); i++)
	{
		theNode = mNodes[i];
		pair<int,int> * location = theNode->getLocation();
		*out << theNode->getId() << ":" << location->first << "," << location->second << endl;
	}
}

//sim setup
void Dispatcher::simSetup (pair<int,int> size, pair<int,int> type, int nodes)
{
	buildMap(size, type);
	buildm_Node(nodes);

	//build traversable nodes list
	for (int x = 0; x < eNodes.size(); x++)
	{
		if (eNodes[x]->isTraversable())
		{
			traversableENodes.push_back(eNodes[x]);
		}
	}

	//place mnodes into starting enodes
	for (int i = 0; i < mNodes.size(); i++)
	{
		theMap.getNode(mNodes[i]->getLocation())->moblist.push_back(mNodes[i]);
	}
}

//run
void Dispatcher::runSim (pair<int,int> size, pair<int,int> type, int nodes)
{
	simSetup(size, type, nodes);
	setupFile();

	char go;
	do
	{
		for (int i = 0; i < mNodes.size(); i++)
		{
			move(mNodes[i]);
		}

		displayMap();
		printData();

		cout << "Would you like to continue (y/n) ?:";

		cin >> go;
	}while (go == 'y' || go == 'Y');
}

//run for
void Dispatcher::runSimFor (int time, pair<int,int> size, pair<int,int> type, int nodes)
{
	simSetup(size, type, nodes);
	setupFile();

	while (currentTime <= time)
	{
		for (int i = 0; i < mNodes.size(); i++)
		{
			move(mNodes[i]);
		}

		displayMap();
		printData();
	}
}

//due to c++ issue
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//fileSetup
void Dispatcher::setupFile ()
{
	bool newName = true;

	int counter = 0;

	string name;

	while (newName)
	{
		name = "simData";
		if (counter != 0)
		{
			name.append(patch::to_string(counter));
		}
		name.append(".dat");

		//test if file exits
    if (FILE *file = fopen(name.c_str(), "r"))
		{
			//if file exists, close it, loop and iterate.
			fclose(file);
			newName = true;
			counter++;
		}
		else
		{
			newName = false;
		}
		cout <<"name:" << name << "counter:" << counter << endl;
	}

	out = new ofstream();
	out->open(name);
}

//fileSetup + name
void Dispatcher::setupFile (string fileName)
{
	out = new ofstream();

	out->open(fileName);
}

//get e_Node using coord variable
e_Node * Dispatcher::getEnode (pair<int,int> * inCoord)
{
	for (int i = 0; i <= eNodes.size(); i++)
	{
		pair<int,int> * temploc = eNodes[i]->getLocation();
		if (temploc->first == inCoord->first && temploc->second == inCoord->second)
		{
			return eNodes[i];
		}
	}
	return 0;
}

//get e_Node using integer input
e_Node  * Dispatcher::getEnode (int x, int y)
{
	int l = eNodes.size();
	e_Node * theNode;
	for (int i = 0; i <= l; i++)
	{
		theNode = eNodes[i];
		pair<int,int> * location = theNode->getLocation();
		if (location->first == x && location->second == y)
		{
			return eNodes[i];
		}
		else
		return NULL;
	}
}
