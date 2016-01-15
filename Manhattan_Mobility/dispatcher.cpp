/*************
*
*	Deven Thiel
*
*	07.14.2015
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
	if (inNode == NULL)
	return false;
	else
	return inNode->isTraversable();
}

//pathfinder
void Dispatcher::pathfinder (m_Node * mobnode)
{
	e_Node * e, * n, * s, * w, * startpos;
	bool emove, nmove, smove, wmove;
	coord * start, * current, * finish;

	start = mobnode->getLocation();
	finish = mobnode->getGoal();
	current = start;
	startpos = getEnode(start);


	while (current != finish)
	{
		/*obtain Moore neighborhood using 4 cardinal points along with 
		the traversability of those points*/
		n = getEnode(current->x, current->y - 1);
		nmove = ckTraversable(n);

		w = getEnode(current->x - 1, current->y);
		wmove = ckTraversable(w);
		
		s = getEnode(current->x, current->y - 1);
		smove = ckTraversable(s);
		
		e = getEnode(current->x + 1, current->y);
		emove = ckTraversable(e);
		
		/*Determine the next step by aligning the x,y coordinates of current
		 with the coordinates of goal. At the establishment of a next step 
		 add that coordinate to the path of the function parameter */
		if (current->x != finish->x || current->y != finish->y)
		{
			if (current->x != finish->x)
			{
				if (emove || wmove)
				{
					if (current->x > finish->x)
						current->x = current->x - 1;
					else if (current->x < finish->x)
						current->x = current->x + 1;
				}
				
			}
			else //(current->y != finish->y)
			{
				if (nmove || smove)
				{
					if (current->y > finish->y)
						current->y = current->y - 1;
					else if (current->y < finish->y)
						current->y = current->y + 1;
				}
			}		
		
			mobnode->path.enqueue(current);
		}
	}
	
}
	
//trip planner
coord * Dispatcher::tripPlanner ()
{
	coord * goal;
	srand (time(NULL));
	e_Node * destination;
	int l = traversableENodes.getLength();
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
	if (mobnode->path.getLength() == 0)
	{
		//trip planner
		mobnode->setGoal(tripPlanner());
		//path finder
		pathfinder(mobnode);
	}
	
	//get enode holding mnode
	tempE = getEnode(mobnode->getLocation());
	//remove mnode from enode
	tempE->moblist.deleteElement(tempE->findMNode(mobnode->getId()));
	//update m_node location
	mobnode->setLocation(mobnode->path.pop());
	//find enode to hold mnode
	tempE = getEnode(mobnode->getLocation());
	//add mnode to enode
	tempE->moblist.addElement();
	tempM = tempE->moblist[tempE->moblist.getLength()];
	tempM = mobnode;
}

//map builder
void Dispatcher::buildMap (coord size, coord type)
{
	e_Node * theENode;
	e_Node * tempE;
	//grow map
	for (int x = 0; x < size.x; x++)
	{
		theMap.addMapCol();
	}
	
	for (int y = 0; y < size.y; y++)
	{
		theMap.addMapRow();
	}
	
	//consider type defined
	int tx = (int)(size.x / type.x);
	int ty = (int)(size.y / type.y);
	
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
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
				traversableENodes.addElement();
				tempE = traversableENodes[traversableENodes.getLength()];
				tempE = theENode;
			}
			else
			{
				theENode->setTraversable(false);
			}
			
			//add to eNodes
			eNodes.addElement();
			tempE = eNodes[eNodes.getLength()];
			tempE = theENode;
			
			//add to map
			theMap.setNode(x,y,theENode);
			if (theMap.getNode(x,y) == NULL)
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
		
		mNodes.addElement();
		tempM = mNodes[mNodes.getLength()];
		tempM = anMNode;
	}
}
	
//display
void Dispatcher::displayMap ()
{
	coord * size = theMap.getMapSize();
	e_Node * theNode;
	
	for (int j = (size->y - 1); j >= 0; j--)
	{
		cout << "+";
		for (int i = 0; i < size->x; i++)
		{
			cout << "-+";
		}
		cout << endl;
		cout << "|";
		for (int i = 0; i < size->x; i++)
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
	
	for (int i = 0; i < mNodes.getLength(); i++)
	{
		theNode = mNodes[i];
		coord * location = theNode->getLocation();
		*out << theNode->getId() << ":" << location->x << "," << location->y << endl;
	}
}

//sim setup
void Dispatcher::simSetup (coord size, coord type, int nodes)
{
	buildMap(size, type);
	buildm_Node(nodes);
	
	/*
	//build traversable nodes list
	for (int x = 0; x < eNodes.getLength(); x++)
	{
		if (eNodes[x]->isTraversable())
		{
			traversableENodes.addElement();
			traversableENodes[traversableEnodes.getLength()] = eNodes[x];
		}
	}
	*/
}
	
//run
void Dispatcher::runSim (coord size, coord type, int nodes)
{
	simSetup(size, type, nodes);
	setupFile();
		
	char go;	
	do
	{
		for (int i = 0; i < mNodes.getLength(); i++)
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
void Dispatcher::runSimFor (int time, coord size, coord type, int nodes)
{
	simSetup(size, type, nodes);
	setupFile();
	
	while (currentTime <= time)
	{
		for (int i = 0; i < mNodes.getLength(); i++)
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
		
    	if (FILE *file = fopen(name.c_str(), "r")) 
		{
        	fclose(file);
        	newName = false;
		}
		else 
		{
        	newName = true;
			counter ++;
    	}
	}
	
	setupFile (name);		
}
	
//fileSetup + name
void Dispatcher::setupFile (string fileName)
{
	out = new ofstream;
	
	out->open(fileName.c_str());
}

//get e_Node using coord variable
e_Node * Dispatcher::getEnode (coord * inCoord)
{
	int l = eNodes.getLength();
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
	int l = eNodes.getLength();
	e_Node * theNode;
	for (int i = 0; i <= l; i++)
	{
		theNode = eNodes[i];
		coord * location = theNode->getLocation();
		if (location->x == x && location->y == y)
		{
			return eNodes[i];
		}
		else 
		return NULL;
	}
}