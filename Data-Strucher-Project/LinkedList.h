#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	Node <T>* Tail;	//Pointer to the tail of the list
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}

	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}

	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}

	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* newnode;
		newnode = new Node<T>;
		newnode->setItem() = data;
		newnode->setNext() = nullptr;
		if (Head == nullptr) {
			Head = newnode;
		}
		else {
			Tail->setNext(newnode);
			Tail = newnode;
		}
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool FindPoint(const T& value)const {
		Node<T>* p = Head;
		while (p) {
			if (p->getvalue() == value)
			{
				return true;
				p = p->getNext();
			}
			else
			{
				return false;
			}

		}
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value) const
	{
		int count = 0;
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == value)
				++count;
			p = p->getNext();
		}
		return count;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst() {
		if (!Head) return;
		Node<T>* p = Head;
		Head = Head->getnext();
		delete p;
	}

	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		if (!Tail) return;
		Node<T>* p = Tail;
		Tail = Tail->getback();
		if (Tail)
			Tail->setNext(nullptr);
		else
			Head = nullptr;
		delete p;
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& Value)
	{
		Node<T>* N = Head;
		Node<T>* Prev = NULL;
		if (N == NULL)return false;
		while (N) {
			if (N->value == Value)
			{
				if (Prev == NULL)
					Head = N->getNext();
				else
					Prev->setNext(N->getNext());
				delete N;
				return true;
			}
			Prev = N;
			N = N->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteAllNodes(const T& Value)
	{
		Node<T>* N = Head;
		Node<T>* Prev = NULL;
		boll f = false;
		if (N == NULL)return false;
		while (N) {
			if (N->value == Value)
			{
				found = true;
				Node<T>* temp = N;
				N = N->getNext();

				if (Prev == NULL)
					Head = N->getNext();
				else
					Prev->setNext(N->getNext());
				delete N;
			}
			Prev = N;
			N = N->getNext();

		}
		return f;
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(LinkedList<T>& L)
	{
		Node<T>* p = Head;
		if (!p) {
			Head = L.Head;
			return;
		}
		else if (!L.Head) {
			return;
		}
		else {
			Tail->setNext(L.Head);
			Tail = L.Tail;
		}
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse()
	{
		Node<T>* prev = nullptr;
		Node<T>* curr = Head;
		Node<T>* next = nullptr;
		Tail = Head;;
		while (curr != nullptr)
		{
			next = curr->getNext();
			curr->setNext(prev);
			prev = curr;
			curr = next;


		}
		Head = prev;
	}
};

#endif // _LINKEDLIST
