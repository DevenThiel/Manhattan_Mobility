/*************
*
*	Deven Thiel
*
*	07.14.2015
*
*	dispatcher class outline for manhattan mobility model
*
*************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "dArray.h"
#include "coord.h"
#include "map.h"
#include "e_Node.h"
#include "m_Node.h"

using namespace std;

class Dispatcher
{
	public:
		
		//default constructor
		Dispatcher();
	
		//default destructor
		~Dispatcher();
	
		//pathfinder
		void pathfinder (m_Node *);
	
		//trip planner
		coord * tripPlanner ();
	
		//move
		void move (m_Node *);
	
		//map builder
		void buildMap (coord, coord);
	
		//m_Node builder
		void buildm_Node(int);
	
		//display
		void displayMap ();
	
		//data file
		void printData ();
	
		//sim setup
		void simSetup (coord, coord, int);
	
		//run
		void runSim (coord, coord, int);
	
		//run for
		void runSimFor (int, coord, coord, int);
	
		//fileSetup
		void setupFile ();
	
		//fileSetup + name
		void setupFile (string);
		
		//get e_Node using coord variable
		e_Node * getEnode (coord *);
		
		//get e_Node using set of integers
		e_Node * getEnode (int, int);
	
	private:
	
		int currentTime;
	
		Map<e_Node> theMap;
	
		DArray<m_Node *> mNodes;
	
		DArray<e_Node *> eNodes;
	
		DArray<e_Node *> traversableENodes;
		
		ofstream * out;
};