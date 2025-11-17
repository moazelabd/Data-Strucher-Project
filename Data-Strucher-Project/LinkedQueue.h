

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_


#include "Node.h"
#include "QueueADT.h"
#include <iostream>
using namespace std;
template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	void circularQueueOnce();
	void display() const;
	bool peek(T& frntEntry)  const;

	~LinkedQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/
template <typename T>
LinkedQueue<T> queueToStack(LinkedQueue<T>& q)
{
	LinkedQueue<T> stackLikeQueue;
	LinkedQueue<T> temp;
	T item;

	while (q.dequeue(item)) {
		stackLikeQueue.enqueue(item);
		temp.enqueue(item);
	}


	while (temp.dequeue(item)) {
		q.enqueue(item);
	}


	return stackLikeQueue;
}

template <typename T>
void LinkedQueue<T>::display() const
{
	Node<T>* current = frontPtr;
	cout << "Queue contents (front ? rear): ";
	while (current != nullptr)
	{
		cout << current->getItem() << " ";
		current = current->getNext();
	}
	cout << endl;
}


template <typename T>
void LinkedQueue<T>::circularQueueOnce() {
	if (isEmpty())
		return;

	T frontItem;
	dequeue(frontItem);   // remove from front
	enqueue(frontItem);   // add to rear
}


template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	if (nodeToDeletePtr == backPtr)
		backPtr = nullptr;

	delete nodeToDeletePtr;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed the destructor
	cout << "\nStarting LinkedQueue destructor...";
	cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue(temp));

	cout << "\n Is LinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding LinkedQueue destructor..." << endl;
}


#endif