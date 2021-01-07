#include<iostream>

#define INF -999
using namespace std;


class node
{
public:
    int key,degree;
    node *parent, *child, *sibling;


    node()
    {
        key=INF;
        degree=INF;
        parent=child=sibling=0;
    }
    node(int k)
    {
        key=k;
        degree=0;
        parent=child=sibling=0;
    }
};


class heapNode
{
public:
    node *head;
    heapNode()
    {

        head=0;

    }
    heapNode(int k)
    {
        head=new node(k);
    }
};

node* getMinElement(heapNode *heap)
{
    if(heap->head==0) return 0;
    else
    {
        node *y=heap->head;
        node *x= heap->head;
        int minKey=99999;

        while(x!=0)
        {
            if(x->key<minKey)
            {
                minKey=x->key;
                y=x;
            }
            x=x->sibling;
        }
        return y;
    }
}

node* binomialLink(node *y,node* z)
{
    cout<<"in link"<<endl;
    y->parent=z;
    y->sibling=z->child;
    z->child=y;
    z->degree++;
    cout<<"link finished"<<endl;
    return z;
}


heapNode* unionHeaps(heapNode *h1,heapNode *h2)
{
    //cout<<"in union func"<<endl;
    heapNode *newHeap=new heapNode();
    node* x=h1->head;
    node* y=h2->head;

    node* current=newHeap->head;
    node* currentPrev=0;

    while(x!=0 || y!=0)
    {
        cout<<"in while    x= "<<x->key<<" y=  "<<y->key
        <<endl;
        //cout<<"x degree : "<<x->degree<<"  y degree : "<<y->degree<<endl;
        if(x==0)
        {
            cout<<"in x=0"<<endl;
            node *temy=y->sibling;
            if(current->degree==y->degree)
            {
                cout<<"in (current->degree==y->degree)"<<endl;
                cout<<"curr key : "<<current->key<<  "  y key : "<<y->key<<endl;
                if(y->key > current->key)
                {
                    node *tem=binomialLink(y,current);

                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
                else
                {
                    node *tem=binomialLink(current,y);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
            }
            else
            {
                current->sibling=y;
                cout<<"current  : "<<current->key<<endl;
                current=y;
                cout<<"current  : "<<current->key<<endl;
            }

            y=temy;
        }

        else if(y==0)
        {
            cout<<"in y=0"<<endl;
            node *temx=x->sibling;
            if(current->degree==x->degree)
            {
                if(y->key > current->key)
                {
                    node *tem=binomialLink(x,current);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
                else
                {
                    node *tem=binomialLink(current,x);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
            }
            else
            {
                current->sibling=x;
                current=x;
            }

            x=temx;
        }




        else if(x->degree==y->degree)
        {

            node *temx=x->sibling;

            node *temy=y->sibling;
            cout<<"in x->degree==y->degree"<<endl;
            //cout<<"temx:  "<<temx<<"temy:  "<<temy<<endl;
            if(current==0)
            {

                if(x->key > y->key)
                {
                    cout<<x->key<<"     "<<y->key<<endl;
                    newHeap->head=binomialLink(x,y);

                    current=newHeap->head;
                    cout<<current->key<<endl;
                }
                else
                {
                    cout<<x->key<<"     "<<y->key<<endl;
                    newHeap->head=binomialLink(y,x);
                    current=newHeap->head;
                    cout<<current->key<<endl;
                }
            }
            else
            {
                if(x->key > y->key)
                {
                    node *tem=binomialLink(x,y);
                    current->sibling=tem;
                    currentPrev=current;
                    current=tem;
                }
                else
                {
                    node *tem=binomialLink(y,x);
                    current->sibling=tem;
                    currentPrev=current;
                    current=tem;
                }
            }
            x=temx;
            y=temy;

        }




        else if(x->degree < y->degree)
        {
            cout<<"in x->degree < y->degree && x!=0"<<endl;
            //cout<<"in hereeeeeee"<<endl;
            node *temx=x->sibling;
            //cout<<temx<<endl;
            if(current==0)
            {
                newHeap->head=x;
                current=newHeap->head;
                cout<<"curr head "<<current->key<<endl;
            }
            else if(current->degree < x->degree)
            {
                current->sibling=x;
                currentPrev=current;
                current=x;
            }
            else if(current->degree==x->degree)
            {
                if(x->key > current->key)
                {
                    node *tem=binomialLink(x,current);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
                else
                {
                    node *tem=binomialLink(current,x);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
            }
            x=temx;
        }




        else if(x->degree > y->degree)
        {
            cout<<"in x->degree > y->degree && y!=0"<<endl;
            node *temy=y->sibling;
            if(current==0)
            {
                newHeap->head=y;
                current=newHeap->head;
            }
            else if(current->degree < y->degree)
            {
                current->sibling=y;
                currentPrev=current;
                current=y;
            }
            else if(current->degree==y->degree)
            {
                if(y->key > current->key)
                {
                    node *tem=binomialLink(y,current);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
                else
                {
                    node *tem=binomialLink(current,y);
                    if(currentPrev==0)
                    {
                        current=tem;
                    }
                    else
                    {
                        currentPrev->sibling=tem;
                        current=tem;
                    }
                }
            }
            y=temy;
        }


    }

    return newHeap;
}


heapNode *insertNode(heapNode *h,int k)
{
   // cout<<"in insert function"<<endl;
    heapNode *tem=new heapNode(k);
    //cout<<tem->head->key<<endl;
    if(h->head==0) return tem;
    else return unionHeaps(tem,h);
}


void printHeap(node *head)
{
    if(head==0) return;
    printHeap(head->sibling);
    cout<<head->key<<"       ";
}

int main()
{
    heapNode *heap= new heapNode();
    int x;
    while(true)
    {
        cin>>x;

        if(x==1) break;
        heap=insertNode(heap,x);
        cout<<heap->head->key<<endl;

    }
    printHeap(heap->head);
}
