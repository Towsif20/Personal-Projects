#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void printWhitespaces(int x)
{
    for(int i=0;i<x;i++)
    {
        cout<<" ";
    }
}

struct Node
{
    int key;
    Node * left;
    Node * right;
};

int maxlevel(Node * root)
{
    if(root == NULL) return 0;

    return max(maxlevel(root->left), maxlevel(root->right)) + 1;
}

bool isAllElemntsNull(vector<Node*> nodes)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i] != NULL)
            return false;
    }

    return true;
}

Node * createNode(int k)
{
    Node * node = new Node;
    node->key = k;

    node->left = node->right = NULL;
}

Node * leftRotate(Node * s)
{
    Node * t = s->right;

    s->right = t->left;

    t->left = s;

    return t;
}

Node * rightRotate(Node * s)
{
    Node * t = s->left;

    s->left = t->right;

    t->right = s;

    return t;
}

Node * maximum(Node* root)
{
    Node * temp = root;

    while(temp->right != NULL)
        temp = temp->right;

    return temp;
}

class SplayTree
{
    int length;

public:
    SplayTree(){length = 0;}

    int getLength(){ return length; }

    Node * splay(Node * root, int key);

    Node * search(Node * root, int key);

    Node * insert(Node * root, int key);

    Node * Delete(Node * root, int key);

    void print(Node * root);

    void printInternalNodes(vector<Node*>, int level, int max_level);

};

Node * SplayTree::splay(Node * root, int key)
{
    if(root == NULL || root->key == key)
        return root;

    if(root->key > key)
    {
        if(root->left == NULL)
            return root;

        if(root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);

            root = rightRotate(root);
        }

        else if(root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);

            if(root->left->right != NULL)
            {
                root->left = leftRotate(root->left);
            }
        }

        if(root->left == NULL) return root;

        else return rightRotate(root);
    }

    else
    {
        if(root->right == NULL)
            return root;

        if(root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);

            root = leftRotate(root);
        }

        else if(root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);

            if(root->right->left != NULL)
            {
                root->right = rightRotate(root->right);
            }
        }

        if(root->right == NULL) return root;

        else return leftRotate(root);
    }
}

Node * SplayTree::search(Node * root, int key)
{
    return splay(root, key);
}

Node * SplayTree::insert(Node * root, int key)
{
    Node * temp = createNode(key);

    if(root == NULL)
    {
        length++;
        return temp;
    }

    root = splay(root, key);

    if(root->key == key) return root;

    if(root->key < temp->key)
    {
        temp->left = root;
        temp->right = root->right;
        root->right = NULL;
    }

    else
    {
        temp->right = root;
        temp->left = root->left;
        root->left = NULL;
    }

    length++;

    return temp;
}

Node * SplayTree::Delete(Node * root, int key)
{
    if(root == NULL) return root;

    Node * temp;

    root = splay(root, key);

    if(root->key != key)
    {
        return root;
    }

    if(root->left == NULL)
    {
        temp = root;

        root = root->right;
    }

    else
    {
        temp = root;

        Node * t = maximum(root->left);

        root = splay(root->left, t->key);

        root->right = temp->right;
    }

    delete temp;

    length--;

    return root;
}

void SplayTree::printInternalNodes(vector<Node*> nodes, int level, int max_level)
{
    if(nodes.empty() || isAllElemntsNull(nodes))
        return;

    int floor = max_level - level;

    int lines = pow(2, max(floor - 1, 0));

    int firstSpaces = pow(2, floor) - 1;

    int betweenspaces = pow(2, floor + 1) - 1;

    printWhitespaces(firstSpaces);

    vector<Node*> v;

    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i] != NULL)
        {
            cout<<nodes[i]->key;
            v.push_back(nodes[i]->left);
            v.push_back(nodes[i]->right);
        }

        else
        {
            v.push_back(NULL);
            v.push_back(NULL);
            cout<"";
        }

        printWhitespaces(betweenspaces);
    }

    cout<<endl;

    for(int i=1;i<=lines;i++)
    {
        for(int j=0;j<nodes.size();j++)
        {
            printWhitespaces(firstSpaces - i);

            if(nodes[j] == NULL)
            {
                printWhitespaces(lines + lines + i + 1);

                continue;
            }

            if(nodes[j]->left != NULL)
                cout<<"/";
            else
                printWhitespaces(1);

            printWhitespaces(i + i - 1);

            if(nodes[j]->right != NULL)
                cout<<"\\";
            else
                printWhitespaces(1);

            printWhitespaces(lines + lines - i);
        }

        cout<<endl;
    }

    printInternalNodes(v, level + 1, max_level);
}

void SplayTree::print(Node * root)
{
    int max_level = maxlevel(root);

    vector<Node*> v;

    v.push_back(root);

    printInternalNodes(v, 1, max_level);
}

int main()
{
    Node* root = NULL;

    int choice, x;

    SplayTree s;

    while(true)
    {
        cout<<"1. insert\n2. search\n3. delete\n4. print\n5. exit\n\n\n";

        cin>>choice;

        if(choice == 1)
        {
            cout<"enter a key to insert\n";
            cin>>x;
            root = s.insert(root, x);
        }

        else if(choice == 2)
        {
            cout<"enter a key to search\n";
            cin>>x;
            root = s.search(root, x);
        }

        else if(choice == 3)
        {
            cout<"enter a key to delete\n";
            cin>>x;
            root = s.Delete(root, x);
        }

        else if(choice == 4)
        {
            s.print(root);
        }

        else if(choice == 5)
        {
            break;
        }

        else
        {
            cout<<"press a valid option\n";
        }
    }

    return 0;
}
