#include "ListElement.h"


ListElement::ListElement(void)
{
	next = nullptr;
	prev = nullptr;
}


ListElement::~ListElement(void)
{
}

//Getters
ListElement* ListElement::getNext() const{
	return next;
}

ListElement* ListElement::getPrev() const{
	return prev;
}

//Setters
void ListElement::setNext(ListElement* e){
	next = e;
}

void ListElement::setPrev(ListElement* e){
	prev = e;
}