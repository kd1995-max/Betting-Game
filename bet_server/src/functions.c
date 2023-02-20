#include "headers.h"
#include "functions.h"

void insertStart (struct Winners_List **head, int data)
{

  // dynamically create memory for this newNode
  struct Winners_List *newNode = (struct Winners_List *) malloc (sizeof (struct Winners_List));

  // assign data value
  newNode->data = data;
  // change the next node of this newNode 
  // to current head of Linked List
  newNode->next = *head;

  //re-assign head to this newNode
  *head = newNode;
  syslog (LOG_ERR,"\n%d Inserted\n", newNode->data);
}

void display (struct Winners_List *node)
{  
  syslog (LOG_ERR,"Winners list starts");
  // as linked list will end when Node is Null
  while (node != NULL)
    {
      syslog (LOG_ERR,"%d ", node->data);
      node = node->next;
    }
  syslog (LOG_ERR,"Winners list ends");
}
