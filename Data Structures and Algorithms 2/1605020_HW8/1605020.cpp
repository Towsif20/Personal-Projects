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



int main()
{

    return 0;
}
