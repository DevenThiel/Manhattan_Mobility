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
	e_Node * e, * n, * s, * w, * startpos;
	bool emove, nmove, smove, wmove;
	pair<int,int> * start, * current, * finish;

	start = mobnode->getLocation();
	finish = mobnode->getGoal();
	current = start;
	startpos = getEnode(start);


	while (current != finish)
	{
		/*obtain Moore neighborhood using 4 cardinal points along with
		the traversability of those points*/
		n = getEnode(current->first, current->second - 1);
		nmove = ckTraversable(n);

		w = getEnode(current->first - 1, current->second);
		wmove = ckTraversable(w);

		s = getEnode(current->first, current->second - 1);
		smove = ckTraversable(s);

		e = getEnode(current->first + 1, current->second);
		emove = ckTraversable(e);

		/*Determine the next step by aligning the x,y coordinates of current
		 with the coordinates of goal. At the establishment of a next step
		 add that coordinate to the path of the function parameter */
		if (current->first != finish->first || current->second != finish->second)
		{
			if (current->first != finish->first)
			{
				if (emove || wmove)
				{
					if (current->first > finish->first)
						current->first = current->first - 1;
					else if (current->first < finish->first)
						current->first = current->first + 1;
				}

			}
			else //(current->second != finish->second)
			{
				if (nmove || smove)
				{
					if (current->second > finish->second)
						current->second = current->second - 1;
					else if (current->second < finish->second)
						current->second = current->second + 1;
				}
			}

			mobnode->path.push_back(current);
		}
	}

}

//trip planner
pair<int,int> * Dispatcher::tripPlanner ()
{
	pair<int,int> * goal;
	srand (time(NULL));
	e_Node * destination;
	int l = traversableENodes.size();
	int r = rand() % l;
	destination = traversableENodes[r];
	goal = destination->getLocation();
	return goal;
}

//move
void Dispatcher::move (m_Node * mobnode)
{
	e_Node * tempE;
	m_Node * tempM;


	//if no path
	if (mobnode->path.size() == 0)
	{
		//trip planner
		mobnode->setGoal(tripPlanner());
		//path finder
		pathfinder(mobnode);
	}

	//get enode holding mnode
	tempE = getEnode(mobnode->getLocation());
	//remove mnode from enode
	tempE->moblist.erase(tempE->moblist.begin() + tempE->findMNode(mobnode->getId()));
	//update m_node location
	//vector pop, should this be changed to a queue?
	mobnode->setLocation(mobnode->path.front());
	mobnode->path.erase(mobnode->path.begin());
	//find enode to hold mnode
	tempE = getEnode(mobnode->getLocation());
	//add mnode to enode
	/*
	tempE->moblist.addElement();
	tempM = tempE->moblist[tempE->moblist.size()];
	tempM = mobnode;
	*/
	//just adding element to the end of the list of new enode
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
			cout << "node: " << theENode << endl;
			theENode->setPermeable(false);
			theENode->setTransmittable(false);

			if (x % tx == 0 || y % ty == 0)
			{
				//traversible

				theENode->setTraversable(true);

				//add traversable list
				/*
				traversableENodes.addElement();
				tempE = traversableENodes[traversableENodes.size()];
				tempE = theENode;*/
				traversableENodes.push_back(theENode);
			}
			else
			{
				theENode->setTraversable(false);
			}

			//add to eNodes
			/*
			eNodes.addElement();
			tempE = eNodes[eNodes.size()];
			tempE = theENode;
			*/
			eNodes.push_back(theENode);

			//add to map
			theMap.setNode(x,y,theENode);
			if (theMap.getNode(x,y) == nullptr)
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

		/*
		mNodes.addElement();
		tempM = mNodes[mNodes.size()];
		tempM = anMNode;
		*/
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

	/*
	//build traversable nodes list
	for (int x = 0; x < eNodes.size(); x++)
	{
		if (eNodes[x]->isTraversable())
		{
			traversableENodes.addElement();
			traversableENodes[traversableEnodes.size()] = eNodes[x];
		}
	}
	*/
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
			//move(mNodes[i]);
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
	out = new ofstream;

	out->open(fileName.c_str());
}

//get e_Node using coord variable
e_Node * Dispatcher::getEnode (pair<int,int> * inCoord)
{
	int l = eNodes.size();
	e_Node * theNode;
	for (int i = 0; i <= l; i++)
	{
		theNode = eNodes[i];
		if (theNode->getLocation() == inCoord)
		{
			return eNodes[i];
		}
		else
		return NULL;
	}
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
