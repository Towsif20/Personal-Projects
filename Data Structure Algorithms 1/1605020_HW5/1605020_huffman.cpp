#include<iostream>
#include<queue>

using namespace std;

struct Node
{
    char c;
    int f;

    Node* left;
    Node* right;

    Node(char c, int f)
    {
        this->c = c;
        this-> f = f;
        left = NULL;
        right = NULL;
    }
};

struct comp
{
    bool operator()(Node * left, Node* right)
    {
        return right->f < left->f;
    }
};

void print(Node * node, string s)
{
     if(node == NULL) return;

     if(node->c != '*')
        cout<<node->c<<" "<<s<<endl;

     print(node->left, s + "0");
     print(node->right, s + "1");
}

void Huffman(int size, char ch[], int fr[])
{
    priority_queue< Node*, vector<Node*>, comp>  pq;

    for(int i=0;i<size;i++)
    {
        Node* t = new Node(ch[i], fr[i]);
        pq.push(t);
    }

    Node * lft, *rght, * newNode;

    while(pq.size() != 1)
    {
        lft = pq.top();
        pq.pop();

        rght = pq.top();
        pq.pop();

        newNode = new Node('*',lft->f + rght->f);

        newNode->left = lft;
        newNode->right = rght;

        pq.push(newNode);
    }

    Node * temp = pq.top();
    print(temp, "");
}

int main()
{
    int size;
    cin>>size;

    char * ch = new char[size];
    int * fr = new int[size];

    for(int i=0;i<size;i++)
    {
        cin>>ch[i];
        cin>>fr[i];
    }

    Huffman(size, ch, fr);

    return 0;
}
