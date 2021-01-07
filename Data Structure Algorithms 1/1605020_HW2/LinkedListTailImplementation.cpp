#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    ListNode * getTail()
    {
        return tail;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;

        if(list == NULL)
        {
            list = newNode;
            tail = newNode;
            length++;
            return SUCCESS_VALUE;
        }
        newNode->next = list ;
        //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node

        length++;
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp ;
            length--;
        }
        else if(temp == tail)
        {
            deleteLast();
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
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

    void printList()
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
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        if(list == NULL)
        {
            insertItem(item);
            return SUCCESS_VALUE;
        }
        ListNode * newNode = new ListNode();
        newNode->item = item;
        newNode->next = NULL;
        tail->next = newNode;
        tail = tail->next;
        length++;

        return SUCCESS_VALUE;

    }

    ListNode * getItemAt(int pos)
    {
         //write your codes here
         if(pos>length || pos<1) return NULL;

         ListNode * temp = list;

         for(int i=1;i<pos;i++)
         {
             temp = temp->next;
         }

         return temp;
    }

    int deleteLast()
    {
        //write your codes here
        if(list == NULL) return NULL_VALUE;

        if(list == tail)
        {
            list = tail = NULL;
            delete list;
            length--;
            return SUCCESS_VALUE;
        }

        ListNode * temp = list;

        while(temp->next != tail)
        {
            temp = temp->next;
        }

        tail = temp;
        temp = temp->next;
        delete temp;
        tail->next = NULL;
        length--;

        return SUCCESS_VALUE;
    }
};
