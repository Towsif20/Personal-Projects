#include<iostream>

using namespace std;

struct Node
{
    int key;
    int degree;

    Node * parent;
    Node * child;
    Node * sibling;
};

Node * CreateNode(int key)
{
    Node * temp = new Node;
    temp->key = key;

    temp->parent = temp->child = temp->sibling = NULL;

    temp->degree = 0;

    return temp;
}


class BinomialHeap
{
    Node * minimum;

public:

    BinomialHeap()
    {
        minimum = NULL;
    }

    void BinomialLink(Node * a, Node * b);
    Node * unionheap(Node* h1, Node * h2);
    Node * Merge(Node * h1, Node * h2);
    Node * insert(Node * a, int k);
    int findMin();
    void print(Node * root);
};

void BinomialHeap::BinomialLink(Node* a, Node* b)
{

    a->parent = b;

    a->sibling = b->child;

    b->child = a;

    b->degree = b->degree + 1;
}

Node* BinomialHeap::Merge(Node* H1, Node* H2)
{
    Node* H = NULL;

    Node* y, *z, *a, *b;

    y = H1;

    z = H2;

    if (y != NULL)
    {

        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;

            else if (y->degree > z->degree)
                H = z;

        }

        else
            H = y;

    }

    else
        H = z;

    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)

        {
            y = y->sibling;
        }

        else if (y->degree == z->degree)
        {
            a = y->sibling;

            y->sibling = z;

            y = a;
        }

        else
        {
            b = z->sibling;

            z->sibling = y;

            z = b;
        }

    }

    return H;
}

Node* BinomialHeap::unionheap(Node* H1, Node* H2)
{

    Node *H = NULL;

    H = Merge(H1, H2);

    if (H == NULL)

        return H;

    Node* prev, *next, *x;

    prev = NULL;

    x = H;

    next = x->sibling;

    while (next != NULL)
    {

        if ((x->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == x->degree))
        {
            prev = x;

            x = next;
        }

        else
	    {
            if (x->key <= next->key)

            {

                x->sibling = next->sibling;

                BinomialLink(next, x);

            }

            else
            {

                if (prev == NULL)
                    H = next;

                else
                    prev->sibling = next;

                BinomialLink(x, next);

                x = next;
            }

	    }

        next = x->sibling;
    }

    return H;
}

Node* BinomialHeap::insert(Node* H, int k)
{
    Node * x = CreateNode(k);

    if(minimum == NULL)
        minimum = x;

    if(minimum->key > k)
        minimum = x;

    Node* H1 = x;

    H = unionheap(H, H1);

    return H;
}

int BinomialHeap::findMin()
{
    if(minimum == 0)
        return 999999;

    return minimum->key;
}

void BinomialHeap::print(Node *h)
{
    while (h)
    {

        cout <<"node "<< h->key << " order "<<h->degree<<endl;
        print(h->child);
        h = h->sibling;
    }

    //cout<<endl;
}

int main()
{
    BinomialHeap bh;

    Node * root = NULL;

    for(int i=0;i<10;i++)
    {
        root = bh.insert(root, 10-i);

        cout<<bh.findMin()<<endl;
    }

    bh.print(root);



    return 0;
}
