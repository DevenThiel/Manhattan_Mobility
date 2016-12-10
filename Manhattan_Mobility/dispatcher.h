/*************
*
*	Deven Thiel
*
*	12.10.2016
*
*	dispatcher class outline for manhattan mobility model
*
*************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include <vector>
#include <utility>

//#include "dArray.h" replaced with std::vector
//#include "coord.h" replaced with std::pair
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
		pair<int,int> * tripPlanner ();

		//move
		void move (m_Node *);

		//map builder
		void buildMap (pair<int,int>, pair<int,int>);

		//m_Node builder
		void buildm_Node(int);

		//display
		void displayMap ();

		//data file
		void printData ();

		//sim setup
		void simSetup (pair<int,int>, pair<int,int>, int);

		//run
		void runSim (pair<int,int>, pair<int,int>, int);

		//run for
		void runSimFor (int, pair<int,int>, pair<int,int>, int);

		//fileSetup
		void setupFile ();

		//fileSetup + name
		void setupFile (string);

		//get e_Node using coord variable
		e_Node * getEnode (pair<int,int> *);

		//get e_Node using set of integers
		e_Node * getEnode (int, int);

	private:

		int currentTime;

		Map<e_Node> theMap;

		vector<m_Node *> mNodes;

		vector<e_Node *> eNodes;

		vector<e_Node *> traversableENodes;

		ofstream * out;
};
