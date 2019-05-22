// ztest.c
#include <stdio.h>

typedef struct _node
{
  int prior;          
  struct _node *next;
} Node;

typedef struct _list
{
  int MAXSIZE;
  int size;
  Node *head;
} List;

List list;

int get_number(char mes[])
{
 int result;
 int c;
 char s[40];
m1:
 printf(mes);
 while ((scanf("%d", &result)) != 1)
 {
   printf("Error: not number - input again \n");
   do c = getchar();
   while (c != '\n' && c != EOF);
   printf(mes);
 }
 if (getchar() != '\n')
 {
   printf("Error: only digits in a number - input again \n");
   do c = getchar();
   while (c != '\n' && c != EOF);
   goto m1;
 }
 return result;
}

void init_queue(List *list, int size) 
{
   list->head = NULL;
   list->size = 0;
   list->MAXSIZE = size;
}

int del_low(List *list)
{
   int del;
   Node* p = list->head;
   Node* q = NULL;
   while (p->next != NULL)
   {
     q = p;
     p = p->next;
   }
   del = p->prior;
   free(p);
   q->next = NULL;
   list->size--; 
   return del;
}

void to_queue(List *list, int prior)
{
   Node* p = (Node*) malloc(sizeof(Node));
   p->prior = prior;
   p->next = list->head;
   list->head = p;
   list->size++; 
}

void from_queue(List *list)
{
   Node* p = list->head;
   list->head = list->head->next;
   free(p);
   list->size--; 
}

void print_queue(List *list)
{
   Node* p = list->head;
   while (p != NULL)
   {
     printf("%d ", p->prior);
     p = p->next;
   }
//   printf("size queue: %d\n",list->size);
   printf("\n");
}

Node * sort_queue(Node* head) 
{
   Node **p = &head;
   while ((*p)->next && (*p)->next->prior < (*p)->prior)
   {
     Node* node = *p;
     *p = node->next;
     node->next = node->next->next;
     (*p)->next = node;
     p = &(*p)->next;
   }
 return head;
}

int main()
{
  int n;
  int m;
  int i = 0;
  int TRANS_PERIOD = 3; // transmit each 3th message
  int SIZEQ; // queue size

  SIZEQ = get_number("Queue size: ");
  init_queue(&list,SIZEQ);

  while (1)
  {
    n = get_number("add new: ");
    to_queue(&list,n);
    list.head=sort_queue(list.head);
    if (list.size > list.MAXSIZE) printf("deleted with low priority: %d\n", del_low(&list)); 
    print_queue(&list);
    if (++i >= TRANS_PERIOD)
    {
      i = 0;
      printf("transmited with high priority: %d\n", list.head->prior);
      if (list.size>0) from_queue(&list);
      print_queue(&list);
    }
  }
  return 0;
}

