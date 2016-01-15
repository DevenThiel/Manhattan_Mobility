#makefile for cabdriver

# <target> : <check for changes>
#	<how to rebuild>

cabdriver: cabdriver.o dArray.o dispatcher.o e_Node.o m_Node.o map.o
	g++ -g cabdriver.o dArray.o dispatcher.o e_Node.o m_Node.o map.o -o cabdriver
	
dArray.o: dArray.cpp dArray.h dArray.t
	g++ -g -c dArray.cpp

map.o: map.cpp map.h map.t dArray.cpp dArray.h dArray.t coord.h
	g++ -g -c map.cpp
	
m_Node.o: m_Node.cpp m_Node.h coord.h
	g++ -g -c m_Node.cpp

e_Node.o: e_Node.cpp e_Node.h m_Node.cpp m_Node.h coord.h
	g++ -g -c e_Node.cpp

dispatcher.o: dispatcher.cpp dispatcher.h e_Node.cpp e_Node.h m_Node.cpp m_Node.h map.cpp map.h map.t dArray.cpp dArray.h dArray.t coord.h
	g++ -g -c dispatcher.cpp

cabdriver.o: cabdriver.cpp dispatcher.cpp dispatcher.h dispatcher.cpp dispatcher.h e_Node.cpp e_Node.h m_Node.cpp m_Node.h map.cpp map.h map.t dArray.cpp dArray.h dArray.t coord.h
	g++ -g -c cabdriver.cpp

clean:
	rm *.o cabdriver
