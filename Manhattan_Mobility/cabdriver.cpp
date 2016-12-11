/*************
*
*	Deven Thiel
*
*	Manhattan_mobility_model "cab" driver
*
*	12/11/16
*
* cabdriver implementation file
*
*************/

#include <iostream>
#include <string>
#include <string.h>

#include "dispatcher.h"

using namespace std;

int stringToInt(string);
void help();
void simulate(int,pair<int,int>,pair<int,int>,int);

int main (int argc, char *argv[])
{

	//default program values, can be changed via parameters, see --help
	int time = 0;
	pair<int,int> size;
	size.first = 3;
	size.second = 3;
	pair<int,int> type;
	type.first = 3;
	type.second = 3;
	int m_Nodes = 1;

	if (argc > 1)
	{
		//deal with each argument
		for (int count = 1; count < argc; count++)
		{
			//help menu
			if (strcmp(argv[count], "-h") == 0 ||
				strcmp(argv[count], "-H") == 0 ||
				strcmp(argv[count], "-?") == 0 ||
				strcmp(argv[count], "--help") == 0 ||
				strcmp(argv[count], "--Help") == 0 )
			{
				help();
			}
			//time to run for
			else if (strcmp(argv[count], "-t") == 0 )
			{
				if (count+1 < argc && argv[count+1][0] != '-')
				{
					count++;
					time = stringToInt(argv[count]);
				}
				else
				{
					cout << "Invalid string for time option.\n";
				}
			}
			//map size
			else if (strcmp(argv[count], "-Ms") == 0 )
			{
				if (count+1 < argc && argv[count+1][0] != '-')
				{
					count ++;
					string temp = argv[count];

					//check if valid input
					bool valid = true;
					int comma= -1;
					for (int z = 0; z < temp.length();z++)
					{
						if (!(48 >= (int)temp[z] && 57 <= (int)temp[z] || 44 == (int)temp[z]))
						{
							valid = false;
							if (44 == (int)temp[z])
							{
								comma = z;
							}
						}
					}

					if (valid && comma >= 1 && comma < temp.length())
					{
						//x
						size.first = stringToInt(temp.substr(0,comma - 1));
						//y
						size.second = stringToInt(temp.substr(comma +1, temp.length()));
					}
					else
					{
						cout << "Invalid string for size option.\n";
					}

				}
				else
				{
					cout << "Invalid string for size option.\n";
				}
			}
			//map type
			else if (strcmp(argv[count], "-Mt") == 0 )
			{
				if (count+1 < argc && argv[count+1][0] != '-')
				{
					count ++;
					string temp = argv[count];

					//check if valid input
					bool valid = true;
					int comma= -1;
					for (int z = 0; z < temp.length();z++)
					{
						if (!(48 >= (int)temp[z] && 57 <= (int)temp[z] || 44 == (int)temp[z]))
						{
							valid = false;
							if (44 == (int)temp[z])
							{
								comma = z;
							}
						}
					}

					if (valid && comma >= 1 && comma < temp.length())
					{
						//x
						type.first = stringToInt(temp.substr(0,comma - 1));
						//y
						type.second = stringToInt(temp.substr(comma +1, temp.length()));
					}
					else
					{
						cout << "Invalid string for type option.\n";
					}

				}
				else
				{
					cout << "Invalid string for type option.\n";
				}
			}
			//mobile nodes
			else if (strcmp(argv[count], "-m") == 0 )
			{
				if (count+1 < argc && argv[count+1][0] != '-')
				{
					count++;
					m_Nodes = stringToInt(argv[count]);
				}
				else
				{
					cout << "Invalid number for mobile nodes option.\n";
				}
			}
			//undefined command
			else
			{
				cout << "Option \"" << argv[count] << "\" undefined.\nsee help menu (-h) for more info.";
			}
		}
    }

	simulate(time,size,type,m_Nodes);

  return 0;
}

int stringToInt(string str)
{
	int result = 0;

	for (int i = 0; i < str.length(); i++)
	{
		result *= 10;
		result += (int)(str[i] - '0');
	}

	return result;
}

void help()
{
	cout << "help menu:\n";
	cout << "\t-H\t\t\t\tHelp menu\n";
	cout << "\t-?\n";
	cout << "\t--Help\n";
	cout << "\t-t\t\t\t\ttime <cycles>\n";
	cout << "\t-Ms\t\t\t\tmap size <x,y>\n";
	cout << "\t-Mt\t\t\t\tmap type <streets x, streets y>\n";
	cout << "\t-m\t\t\t\tmobile nodes <nodes>\n";
}

void simulate(int t,pair<int,int> ms,pair<int,int> mt,int n)
{
	Dispatcher theSim;

	if (t == 0)
	{
		theSim.runSim(ms,mt,n);
	}
	else
	{
		theSim.runSimFor(t,ms,mt,n);
	}
}
