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

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

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
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
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
        printf("Length: %d\n",length);
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
        ListNode * temp = list;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        ListNode * newNode = new ListNode();
        newNode->item = item;
        newNode->next = NULL;
        temp->next = newNode;
        length++;

        return SUCCESS_VALUE;
    }

    int insertAfter(int oldItem, int newItem)
    {
        //write your codes here
        ListNode * temp;
        ListNode * newNode = new ListNode();
        temp = searchItem(oldItem);

        if(temp != NULL)
        {
            newNode->item = newItem;
            newNode->next = temp->next;
            temp->next = newNode;
            length++;
            return SUCCESS_VALUE;
        }

        return NULL_VALUE;
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

    int deleteFirst()
    {
        if(list == NULL) return NULL_VALUE;
        //write your codes here
        ListNode * temp = list;
        list = list->next;
        delete temp;
        length--;

        return SUCCESS_VALUE;

    }


    ~LinkedList()
    {
        //write your codes here
        int l = length;

        for(int i=0;i<l;i++)
        {
            deleteFirst();
        }
    }

};
