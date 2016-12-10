#makefile for cabdriver

# <target> : <check for changes>
#	<how to rebuild>

cabdriver: cabdriver.o dispatcher.o e_Node.o m_Node.o map.o
	g++ -g cabdriver.o dispatcher.o e_Node.o m_Node.o map.o -o cabdriver

map.o: map.cpp map.h map.t
	g++ -g -c map.cpp

m_Node.o: m_Node.cpp m_Node.h
	g++ -g -c m_Node.cpp

e_Node.o: e_Node.cpp e_Node.h m_Node.cpp m_Node.h
	g++ -g -c e_Node.cpp

dispatcher.o: dispatcher.cpp dispatcher.h e_Node.cpp e_Node.h m_Node.cpp m_Node.h map.cpp map.h map.t
	g++ -g -c dispatcher.cpp

cabdriver.o: cabdriver.cpp dispatcher.cpp dispatcher.h dispatcher.cpp dispatcher.h e_Node.cpp e_Node.h m_Node.cpp m_Node.h map.cpp map.h map.t
	g++ -g -c cabdriver.cpp

clean:
	rm *.o cabdriver
