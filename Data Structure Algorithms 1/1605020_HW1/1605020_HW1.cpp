#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>

using namespace std;

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class Arraylist
{
    int listMaxSize;
    int * list;
    int length;

public:

    int getLength();
    int insertItemAt(int pos, int item);

    void initializeList()
    {
        listMaxSize = LIST_INIT_SIZE;
        list = (int*)malloc(sizeof(int)*listMaxSize) ;
        length = 0 ;
    }

    void Shrink()
    {
        if(listMaxSize > LIST_INIT_SIZE && length*2 <= listMaxSize)
        {
            int * temp;
            listMaxSize = listMaxSize/2;
            temp = (int*) malloc(listMaxSize*sizeof(int));

            for(int i=0;i<length;i++)
            {
                temp[i] = list[i];
            }

        free(list);
        list = temp;
    }
}

    int searchItem(int item)
    {
        int i = 0;
        for (i = 0; i < length; i++)
        {
            if( list[i] == item )
            {
                printf("Item found\n");
                return i;
            }
        }
        printf("Item not found\n");
        return NULL_VALUE;
    }

    int insertItem(int newitem)
    {
        if(list == NULL)
        {
            initializeList();
        //list = (int*) malloc(LIST_INIT_SIZE*sizeof(int));
        }
        int * tempList ;
        if (length == listMaxSize)
        {
		//allocate new memory space for tempList
            listMaxSize = 2 * listMaxSize ;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        };

        list[length] = newitem ; //store new item
        length++ ;
	//printf("Item inserted.\n");
        return SUCCESS_VALUE ;
    }

int insertItemAt(int pos, int item)
{
    if(list == NULL)
    {
        initializeList();
        //list = (int*) malloc(LIST_INIT_SIZE*sizeof(int));
    }

    if(pos >= length)
    {
        printf("invalid index\n");
        return NULL_VALUE;
    }
    else
    {
        int * tempList;
        if(length == listMaxSize)
        {
        listMaxSize = 2 * listMaxSize;
        tempList = (int*) malloc(listMaxSize*sizeof(int));

        for(int i=0;i<length;i++)
        {
            tempList[i] = list[i];
        }
        free(list);
        list = tempList;
        }
        list[length] = list[pos];
        list[pos] = item;
        length++;
        printf("Item inserted at the given index.\n");
        return SUCCESS_VALUE;
    }
}

int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length )
    {
        printf("invalid index\n");
        return NULL_VALUE;
    }
	list[position] = list[length-1] ;
	length-- ;
	Shrink();
	printf("Item deleted at the given index\n");
	return SUCCESS_VALUE ;
}

int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	Shrink();
	printf("Item deleted\n");
	return SUCCESS_VALUE ;
}

void deleteLast()
{
    length--;
    int * temp;
    temp = (int*) malloc(length*sizeof(int));
    for(int i=0;i<length;i++)
    {
        temp[i] = list[i];
    }
    free(list);
    list = temp;
    Shrink();
    //printf("Last item deleted\n");
}

void printList()
{
   if(list != NULL)
   {
        int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\nCurrent size: %d, current length: %d\n", listMaxSize, length);
   }
    //cout<<length<<" "<<getLength()<<endl;
}

int getLength()
{
    //if(list == NULL) return 0;
    return length;
}
};



void deleteAll()
{
    free(list);
    int * temp;
    temp = (int*) malloc(LIST_INIT_SIZE*sizeof(int));
    list = temp;
    length = 0;
    //printf("All items deleted\n");
}

void clear()
{
    free(list);
}

/*
int main(void)
{
    initializeList();

    while(1)
    {
        printf("\n1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Insert a new item at a given index. 5. Delete the last item\n");
        printf("6. Delete all items. 7. Clear the list. 8. Print. 9. exit.\n\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            int pos, item;
            printf("Insert the index you want to insert in: \n");
            scanf("%d",&pos);
            printf("Insert the new item: \n");
            scanf("%d",&item);
            insertItemAt(pos, item);
        }
        else if(ch==5)
        {
            deleteLast();
        }
        else if(ch==6)
        {
            deleteAll();
        }
        else if(ch==7)
        {
            clear();
        }
        else if(ch==8)
        {
            printList();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
*/
///*
int main()
{
    bool valid = true;
    char s[80];

    while(1)
    {
        printf("\nEnter a postfix expression: (Input '0' to exit)\n");
        initializeList();
        scanf("%s",s);
        if(s[0] == '0') break;

        int i=0;
        while(s[i])
        {
            if(s[i] >= '0' && s[i] <= '9')
            {
                insertItem(s[i] - 48);
            }

            if(s[i] ==  '+')
            {
                int x = list[length-1] + list[length-2];

                deleteLast();
                deleteLast();

                insertItem(x);
            }

            if(s[i] ==  '-')
            {
                int x = list[length-2] - list[length-1];

                deleteLast();
                deleteLast();

                insertItem(x);
            }

            if(s[i] ==  '*')
            {
                int x = list[length-1] * list[length-2];

                deleteLast();
                deleteLast();

                insertItem(x);
            }

            if(s[i] ==  '/')
            {
                int x;

                if(list[length-1] != 0)
                {
                    x = list[length-2] / list[length-1];

                    deleteLast();
                    deleteLast();

                    insertItem(x);
                }

                else
                {
                    valid = false;
                    printf("Invalid input\n");
                    break;
                }
            }
            i++;
        }

        if(valid && length == 1)
        {
            printf("%d\n",list[0]);
            //printList();
        }
        else
        {
            printf("invalid input\n");
        }
        deleteAll();
        //printList();

        clear();
        //printList();

    }
    return 0;
}
//*/















