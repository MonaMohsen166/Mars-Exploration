#pragma once
#include "Node.h"



template<typename T>
class Stack
{
protected:
	Node<T>* head;
	T data;
	int count;

public:
	Stack();
	void push(const T NewItem);
	T peek();
	void pop(T&) ;
	bool isEmpty() const;
	Stack(const Stack<T>& aStack);
	const T* toArray(int& count);

};

template<typename T>
Stack<T>::Stack()
{
	count = 0;
	head = nullptr;
}


template<typename T>
Stack<T>::Stack(const Stack<T>& aStack)
{
	Node<T>* orgptr = aStack->head;
	if (orgptr == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new Node<T>();
		head->setItem(orgptr->getItem());
		// Point to first node in new chain
		Node<T>* newChainPtr = head;
		// Copy remaining nodes
		while (orgptr != nullptr)
		{
			orgptr = orgptr->getNext();
			T nextItem = orgptr->getItem();
			Node<T>* newNodePtr = new Node<T>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}

template<typename T>
bool Stack<T>::isEmpty()const
{
	return head == nullptr;
}
template<typename T>
void Stack<T>::push(const T NewItem)
{
	Node<T>* newNodePtr = new Node<T>(NewItem, head);
	head = newNodePtr;
	newNodePtr = nullptr;
}
template<typename T>
T Stack<T>::peek()
{
	return head->getItem();
}



template<typename T>
void Stack<T>::pop(T& item)
{

	if (!isEmpty())
	{
		Node<T>* nodeToDeletePtr = head;
		item = head->getItem();
		head = head->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
	}

}
template <typename T>
const T* Stack<T>::toArray(int& count)
{
	count = 0;

	if (!head)
		return nullptr;
	Node<T>* p = head;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = head;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
