#pragma once
#include "ListElement.h"

class List
{
public:
	List(void);
	virtual ~List(void);

	void addElement(ListElement *e);
	void removeElement(ListElement *e);

	//getters
	ListElement* getHead() const;
	ListElement* getTail() const;

private:
	ListElement *head;
	ListElement *tail;
};

