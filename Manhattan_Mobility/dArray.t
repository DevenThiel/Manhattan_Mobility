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
 * Template implimentation file to impliment templated portions of a
 * 	class providing functionality for a dynamically sized array.
 *
 ************/

//default constructor
template <class T>
DArray<T>::DArray ()
{
	length = 0;
	dataP = 0;
}

//constructor taking length of array
template <class T>
DArray<T>::DArray (int inLength)
{
	length = inLength;
	dataP = new T[inLength];
}

//default destructor
template <class T>
DArray<T>::~DArray ()
{
	if (length == 1)
	{
		delete dataP;
	}
	else if (length > 1)
	{
		delete[] dataP;
	}
}

//copy constructor
template <class T>
DArray<T>::DArray (const DArray<T> & other)
{
	length = other.length;

	if (length == 1)
	{
		delete dataP;
	}
	else if (length > 1)
	{
		delete[] dataP;
	}

	//delete[] dataP;

	dataP = new T[length];

	for (int i = 0; i < length; i++)
	{
		dataP[i] = other.dataP[i];
	}
}

//remove one element from array (length--)
template <class T>
void DArray<T>::deleteElement ()
{
	deleteElement(length - 1);
}

//remove one specific element from array (length--)
template <class T>
void DArray<T>::deleteElement (int inTarget)
{
	length--;
	//create new array of correct size
	T *tempP = new T[length];
	//copy relevent parts of current array
	for (int i = 0; i <= length; i++)
	{
		if (i < inTarget)
		{
			tempP[i] = dataP[i];
		}
		else if (i > inTarget)
		{
			tempP[i - 1] = dataP[i];
		}
	}

	//delete old array
	delete[] dataP;

	//move pointer
	dataP = tempP;
}

//add one element to array (length++)
template <class T>
void DArray<T>::addElement ()
{
	length++;
	/* corrupt data?
	T nerl[1] = {};
	T & n0ll = nerl[0];
	*/
	//create new array of correct size
	T *tempP;

	tempP = new T[length];

	//zero new array
	for (int i = 0; i < length; i++)
	{
		tempP[i] = n0ll;
	}

	//copy current array
	for (int i = 0; i < (length - 1); i++)
	{
		tempP[i] = dataP[i];
	}

	//delete (free) old memory
	delete[] dataP;

	//move pointer
	dataP = tempP;
}

//return length
template <class T>
int DArray<T>::getLength () const
{
	return length;
}

//return address of element
template <class T>
T DArray<T>::getElement (int inTarget)
{
	return dataP[inTarget];
}

//member access
template <class T>
T DArray<T>::operator[](int num)
{
    return dataP[num];
}

//overload = operator
template <class T>
DArray<T>& DArray<T>::operator= (const DArray<T> & other)
{
	length = other.length;

	delete[] dataP;

	dataP = new T[length];

	for (int i = 0; i < length; i++)
	{
		dataP[i] = other.dataP[i];
	}

	return *this;
}

//stack functionality

//stack push
template <class T>
void DArray<T>::push (T item)
{
	addElement();

	dataP[length - 1] = item;
}

//stack pop
template <class T>
T DArray<T>::pop ()
{
	T temp = dataP[length - 1];

	deleteElement();

	return temp;
}

//stack object push
template <class T>
void DArray<T>::pushO (T* itemPtr)
{
	addElement();

	dataP[length - 1] = *itemPtr;
}

//stack object pop
template <class T>
T * DArray<T>::popO ()
{
	T * temp = &(dataP[length - 1]);

	deleteElement();

	return temp;
}

//queue functionality

//queue add
template <class T>
void DArray<T>::enqueue (T item)
{
	addElement();

	dataP[length - 1] = item;
}

//queue remove
template <class T>
T DArray<T>::dequeue ()
{
	T temp = dataP[0];

	deleteElement(0);

	return temp;
}

//queue object add
template <class T>
void DArray<T>::enqueueO (T* itemPtr)
{
	addElement();

	dataP[length - 1] = *itemPtr;
}

//queue object remove
template <class T>
T* DArray<T>::dequeueO ()
{
	T * temp = new T;

	*temp = dataP[0];

	deleteElement(0);

	return temp;
}
