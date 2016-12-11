# Manhattan_Mobility

12/10/16
Currently this project is being transitioned from a custom dynamic array library to standard c++ vector based lists.
Coord class also to be replaced with genaric std::pair

*.h updated
makefile updated
*.cpp updated
*.t updated

most of transition in complete. dispatcher.cpp still needs functionality updates from build in features of DArray to work with std::vector

Transition complete.

12/11/16

debugging seg fault in driver - not running as far as it was with old DArray/Coord, likely still something that needs to be changed is causing this.

no more seg fault.

Output file working, data printing to it.
inf loop somewhere inside of the dispatcher.move();. I think pathfinder still needs to be finished?

Removed the files for dArray and coord which are no longer used.
