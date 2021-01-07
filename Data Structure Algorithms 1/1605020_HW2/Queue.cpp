#include<stdio.h>
#include<stdlib.h>
#include"LinkedListTailImplementation.cpp"


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class Queue
{
    LinkedListWithTail ll;
public:
    Queue()
    {

    }

    void enqueue(int item)
    {
        //write your codes here
        ll.insertItem(item);
    }

    int dequeue()
    {
       //write your codes here
       ListNode * temp = ll.getItemAt(ll.getLength());
       if(temp != NULL)
       {
           int res = temp->item;
           ll.deleteLast();
           return res;
       }

       return NULL_VALUE;
    }

    void printQ()
    {
        ll.printList();
    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("1. Enque. 2. Deque. 3. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            printf("%d\n",item);
        }
        else if(ch==3)
        {
            break;
        }
        else
        {
            qu.printQ();
        }
    }

}

