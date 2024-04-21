#pragma once

template < typename T>
class PNode
{
private:
	T item; // A data item
	PNode<T>* next;
	int priority; // Pointer to next node
public:
	PNode();
	PNode(const T& r_Item);	//passing by const ref.
	PNode(const T& r_Item, PNode<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(PNode<T>* nextNodePtr);
	T getItem() const;
	PNode<T>* getNext() const;
	void setP(int P);
	int getP() const;
}; // end Node


template < typename T>
PNode<T>::PNode()
{
	next = nullptr;
}

template < typename T>
PNode<T>::PNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
PNode<T>::PNode(const T& r_Item, PNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void PNode<T>::setNext(PNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T PNode<T>::getItem() const
{
	return item;
}

template < typename T>
PNode<T>* PNode<T>::getNext() const
{
	return next;
}
template < typename T>
void PNode<T>::setP(int P)
{
	priority = P;
}
template < typename T>
int PNode<T>::getP() const
{
	return priority;
}


