#pragma once
class ListElement
{
public:
	ListElement(void);
	virtual ~ListElement(void);

	//Getters
	ListElement* getNext() const;
	ListElement* getPrev() const;

	//Setters
	void setNext(ListElement*);
	void setPrev(ListElement*);

private:
	ListElement* next;
	ListElement* prev;
};

