/************
 * 
 * Deven Thiel
 * 
 * 07.08.2015
 *
 * v1.0 - addition of operator overloading
 * v1.1 - addition of stack functionality
 * v1.2 - addition of queue functionality
 *
 * Header file to declare a class that impliments a method for use of a 
 * 	dynamically sized array.
 * 
 ************/
#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>

using namespace std;

template <class T>
class DArray
{
	public:
		//Default constructor
		DArray();
		
		//Constructor taking a variable length	 
		DArray(int);
	
		//copy constructor
		DArray(const DArray &);

		//Default destructor
		~DArray();
		
		void deleteElement();
	 
		void deleteElement(int);
		
		void addElement ();
		
		int getLength () const;
		
		T getElement (int);
	
		T operator[] (int);
	
		DArray<T>& operator= (const DArray<T> & other);
	
		//stack functionality
	
		void push (T);
		T pop ();
	
		void pushO (T*);
		T* popO ();
	
		//queue functionality
	
		void enqueue (T);
		T dequeue ();
	
		void enqueueO (T*);
		T* dequeueO ();
	
		//todo: search and sort functions

	private:
		int length;
		
		T * dataP;
};

#include "dArray.t"
 
#endif
