#include<iostream>
#include"PNode.h"
#pragma once
using namespace std;

template<class T>
class PriQueue
{
private:
	PNode<T>* Head;
	int count;
public:
	PriQueue();
	PriQueue(const PriQueue& pq);
	~PriQueue();
	bool isEmpty() const;
	bool add(const T& newEntry, int x);
	bool remove(T& TopEntry);
	bool peek(T& TopEntry);
	const T* toArray(int& count);
};
template<class T>
PriQueue<T>::PriQueue()
{
	Head = NULL;
	count = 0;
}
template<class T>
PriQueue<T>::PriQueue(const PriQueue& aPqueue)
{
	PNode<T>* orgptr = aPqueue.Head;
	if (orgptr == NULL)
	{
		Head = NULL;
		count = 0;
	}
	else
	{
		Head = new PNode<T>();
		Head->setItem(orgptr->getItem());
		Head->setP(orgptr->getP());
		PNode<T>* newChainPtr = Head;
		while (orgptr != NULL)
		{
			orgptr = orgptr->getNext();
			T nextItem = orgptr->getItem();
			PNode<T>* newNodePtr = new PNode<T>(nextItem);
			newNodePtr->setP(orgptr->getP());
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}
template<class T>
bool PriQueue<T>::isEmpty() const
{
	if (!Head)
	{
		return true;
	}
	return false;
}
template<class T>
bool PriQueue<T>::remove(T& TopEntry)
{
	if (isEmpty())
		return false;
	PNode<T>* nodeToDeletePtr = Head;
	TopEntry = Head->getItem();
	Head = Head->getNext();
	count--;



	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;
}
template<class T>
bool PriQueue<T>::add(const T& newEntry, int x)
{
	PNode<T>* newNode = new PNode<T>(newEntry);
	if (newNode == nullptr)
	{
		return false;
	}
	newNode->setP(x);
	PNode<T>* ptr = Head;
	if (isEmpty())
	{
		Head = newNode;
		Head->setNext(NULL);
		count++;
		return true;
	}
	if (newNode->getP() > Head->getP())
	{
		newNode->setNext(Head);
		Head = newNode;
		count++;
		return true;
	}
	while (ptr->getNext() && newNode->getP() < ptr->getNext()->getP())
	{
		ptr = ptr->getNext();
	}
	count++;
	newNode->setNext(ptr->getNext());
	ptr->setNext(newNode);
	return true;
}
template<class T>
bool PriQueue<T>::peek(T& TopEntry)
{
	if (isEmpty())
		return false;

	TopEntry = Head->getItem();
	return true;
}
template <typename T>
PriQueue<T>::~PriQueue()
{
}
template <typename T>
const T* PriQueue<T>::toArray(int& count)
{
	count = 0;

	if (!Head)
		return nullptr;
	//counting the no. of items in the Queue
	PNode<T>* p = Head;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = Head;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
