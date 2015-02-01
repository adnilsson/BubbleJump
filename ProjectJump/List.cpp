#include "List.h"


List::List(void)
{
	//Start with an empty list
	head = nullptr;
	tail = nullptr;
}


List::~List(void)
{
	//Remove all elements in the list
	while(head != nullptr) removeElement(head);
}

//New elements are placed last.
void List::addElement(ListElement *e){
	
	//Case of empty list
	if(head == nullptr && tail == nullptr){
		head = e;
		tail = e; 
	}
	else{
		e->setPrev(tail);
		tail->setNext(e);
		tail = e;
	}
}

//Find and remove an element.
void List::removeElement(ListElement *e){
	//Empty list or invalid parameter
	if(head == nullptr && tail == nullptr || e == nullptr){
		return;
	}
	
	if(head == tail ){ //One bubble left in list. (Though not possible in game)

		delete head; 

		head = nullptr;
		tail = nullptr;
		return;
	}

	if(e == head){
		head = head->getNext();
	}
	else if(e == tail){
		
		e->getPrev()->setNext(nullptr);

		tail = tail->getPrev();
	}
	else{
		e->getPrev()->setNext(e->getNext());
		e->getNext()->setPrev(e->getPrev());
	}

	delete e;
}

//Getters
ListElement* List::getHead() const{
	return head;
}

ListElement* List::getTail() const{
	return tail;
}