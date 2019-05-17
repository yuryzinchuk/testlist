// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Node {

public:
    int prior;
    Node *next;
};

typedef Node * ListType;

// Insertion sort
void InsertAndSort(ListType &list) {
    ListType *p = &list;

    while ( (*p)->next && (*p)->next->prior < (*p)->prior)
    {
      ListType node= *p;
      *p=node->next;
      node->next=node->next->next;
      (*p)->next=node;
      p= &(*p)->next;
    }
}

void ShowQueue(ListType list) {
    Node *p = list;

    std::cout << std::endl;
    while (p!=NULL)  
    {
     std::cout << p->prior << " ";
     p=p->next;
    }
}

int main()
{
    int n;
	int m;
	int i=0;
	int SIZEQ; // Queue size
	int TRANS_SLOW=3; // transmit each 3th message
    Node *head=0;

	std::cout << "Queue size: "; std::cin >> SIZEQ;
    std::cout << std::endl;

    while (std::cout << "add new: ", std::cin >> n)
    {
	 // insert a new message in the head of the list (to the queue)
     Node *p=new Node;
     p->prior=n;
     p->next=head;
     head=p;
	 // insertion sort
     InsertAndSort(head);
	 // show sorted queue
	 m=0;
	 p=head;
     while (p!=NULL)
	 {
      std::cout << p->prior << " ";
	  m++;
	  if (p->next != NULL)
	  {
       // control of size 
	   if (m==SIZEQ) 
	   {
        // delete a message with low priority
        std::cout << "deleted with low priority: " << p->next->prior;
	    delete p->next;
		p->next = NULL;
	  };
	 };
	 p=p->next;
	}
	// transmit a message with high priority
	if (++i >= TRANS_SLOW)
	{
     i=0;
 	 p=head;
	 head=head->next;
     std::cout << std::endl << "transmit with high priority: " << p->prior;
	 delete p;
	 ShowQueue(head);
	 };
     std::cout << std::endl;
    }
}