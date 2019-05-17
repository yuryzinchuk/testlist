// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Node {

public:
    int data;
    Node *next;
};

typedef Node * ListType;

// сортування по пріоритету методом вставки
void InsertAndSort(ListType &list) {
    ListType *p = &list;

    while ( (*p)->next && (*p)->next->data < (*p)->data)
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
	 std::cout << p->data << " ";
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
		// вставка нового повідомлення в голову списку (в чергу) 
        Node *p=new Node;
        p->data=n;
        p->next=head;
        head=p;
		// сортування по пріоритету методом вставки
        InsertAndSort(head);
		// виведення відсортованого по пріоритетах вмісту черги 
		m=0;
		p=head;
        while (p!=NULL)
		{
         std::cout << p->data << " ";
		 m++;
		 if (p->next != NULL)
		 {
          // перевірка на допустимий розмір черги
		  if (m==SIZEQ) 
		  {
            // видалення повідомлення з найнижчим пріоритетом
            std::cout << "deleted with low prioity: " << p->next->data;
			delete p->next;
			p->next = NULL;
		  };
		 };
	     p=p->next;
		}
		// передача повідомлення з найвищим пріоритетом (з швидкістю кожен третій від нових надійшовших повідомлень в чергу)
		if (++i >= TRANS_SLOW)
		{
         i=0;
 		 p=head;
		 head=head->next;
         std::cout << std::endl << "transmit with high prioity: " << p->data;
		 delete p;
		 ShowQueue(head);
		};
        std::cout << std::endl;
    }
}