#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
    ListNode * prev;
};


class LinkedListDoubly
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListDoubly()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertFirst(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;

        if(list==0) //inserting the first item
        {
            newNode->next = 0;
            newNode->prev = 0;
            list = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = list;
            list->prev = newNode;
            newNode->prev = 0;
            list = newNode;
        }
        length++;
        return SUCCESS_VALUE ;
    }

    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printListForward()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        if(list != NULL)
            printf("head: %d    tail: %d\n",list->item,tail->item);

        printf("Length: %d\n",length);

    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        if(list == NULL)
        {
            insertFirst(item);
            return SUCCESS_VALUE;
        }
        //write your codes here
        ListNode * newNode = new ListNode();
        newNode->item = item;
        ListNode * temp = tail;
        newNode->next = NULL;
        newNode->prev = temp;
        temp->next = newNode;
        tail = tail->next;

        length++;

        return SUCCESS_VALUE;
    }

    int deleteLast() ///needs attention
    {
        //write your codes here

        if(list == NULL) return NULL_VALUE;

        if(list == tail)
        {
            list->next = NULL;
            list = tail = NULL;
            delete list;
            length--;
            return SUCCESS_VALUE;
        }

        ListNode * temp = tail;
        tail = temp->prev;
        delete temp;
        tail->next = NULL;
        length--;

        return SUCCESS_VALUE;
    }

    void printListBackward()
    {
        //will print the list backward starting from the tail position
        ListNode * temp = tail;

        while(temp != NULL)
        {
            printf("<-%d",temp->item);
            temp = temp->prev;
        }
        printf("\n");
        if(list != NULL)
            printf("head: %d    tail: %d\n",list->item,tail->item);

        printf("Length: %d\n",getLength());
    }

};

int main(void)
{
    LinkedListDoubly ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertFirst(item);
            //ll.insertLast(item);
        }
        else if(ch==2)
        {
            int item = ll.deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            ll.printListForward();
        }
        else if(ch==5)
        {
            ll.printListBackward();
        }
        else if(ch==6)
        {
            break;
        }
    }

}
