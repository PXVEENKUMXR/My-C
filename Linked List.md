## Reverse a Linked List
```c
#include<stdio.h>
#include<stdlib.h>

struct node
{
        int data;
        struct node *next;
};

struct node *head = NULL;
void addnode(int data)
{
        struct  node *new = malloc(sizeof(struct node));

        new->data = data;
        new->next= NULL;
        if(head ==NULL)
        {
                head=new;
                return;
        }
        struct node *trav;
        trav=head;
        while(trav->next!=NULL)
        {
                trav=trav->next;
        }
        trav->next=new;
}
void reverse()
{
        struct node *current = head;
        struct node *prev =NULL, *next =NULL;

        while(current!=NULL)
        {
                next = current->next;
                current->next=prev;
                prev=current;
                current=next;
        }
        head=prev;
}

void display()
{
        struct node *trav=head;
        while(trav!=NULL)
        {
                printf("%d->",trav->data);
                trav=trav->next;
        }

        printf("NULL\n");

}

int main()
{
        addnode(1);
        addnode(2);
        addnode(3);
        addnode(4);
        addnode(5);
        printf("Linked list : ");
        display();
        printf("Reversed List : ");
        reverse();
        display();
}
```
