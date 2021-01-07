#include<iostream>
#include<fstream>

using namespace std;

void swap(int & a, int & b)
{
    int t = a;
    a = b;
    b = t;
}

class MinHeap
{
    int capacity;
    int ** arr;
    int len;

public:

    int** getArr(){ return arr; }

    //int getItem(int i){ return arr[i]; }

    int leftChildIndex(int i)
    {
        return 2*i + 1;
    }

    int rightChildIndex(int i)
    {
        return 2*i + 2;
    }

    int parentIndex(int i)
    {
        return (i - 1) / 2;
    }

    bool hasLeftChild(int i)
    {
        return leftChildIndex(i) < len;
    }

    bool hasRightChild(int i)
    {
        return rightChildIndex(i) < len;
    }

    bool hasParent(int i)
    {
        return parentIndex(i) >= 0;
    }

    MinHeap(int cap);
    int findMinEdge();
    int findMinEdgeFirstNode();
    int findMinEdgeSecondNode();
    void insert(int v1, int v2, int w);
    int extractMin();
    void deleteMin();
    void replace(int item);
    void heapify(int * vertices1, int * vertices2, int * weight, int length);
    int size();
    bool isEmpty();
    void decreaseKey(int old, int val);
    void increaseKey(int old, int val);
    void deleteItem(int item);
    void siftUp(int);
    void siftDown(int);
    void print();
    ~MinHeap();

};

MinHeap::MinHeap(int cap)
{
    capacity = cap;
    len = 0;
    arr = new int*[3];

    arr[0] = new int[capacity];
    arr[1] = new int[capacity];
    arr[2] = new int[capacity];
}

int MinHeap::size()
{
    return len;
}

bool MinHeap::isEmpty()
{
    return len == 0;
}

int MinHeap::findMinEdge()
{
    if(len == 0) return INT_MAX;

    return arr[0][0];
}

int MinHeap::findMinEdgeFirstNode()
{
    if(len == 0) return INT_MAX;

    return arr[1][0];
}

int MinHeap::findMinEdgeSecondNode()
{
    if(len == 0) return INT_MAX;

    return arr[2][0];
}

void MinHeap::siftDown(int i)
{
  int left = leftChildIndex(i);
  int right = rightChildIndex(i);

  int smallest = i;

  if(left<len && arr[0][left] < arr[0][smallest])
    smallest = left;

  if(right<len && arr[0][right] < arr[0][smallest])
    smallest = right;

  if(smallest != i)
  {
      swap(arr[0][smallest], arr[0][i]);
      swap(arr[1][smallest], arr[1][i]);
      swap(arr[2][smallest], arr[2][i]);

      siftDown(smallest);
  }
}

void MinHeap::siftUp(int i)
{
    if(i && arr[0][parentIndex(i)] >= arr[0][i])
    {
        swap(arr[0][i], arr[0][parentIndex(i)]);
        swap(arr[1][i], arr[1][parentIndex(i)]);
        swap(arr[2][i], arr[2][parentIndex(i)]);

        siftUp(parentIndex(i));
    }
}

void MinHeap::insert(int v1, int v2, int w)
{
    if(len == capacity) return;

    arr[0][len] = w;
    arr[1][len] = v1;
    arr[2][len] = v2;

    len++;
    int index = len-1;

    siftUp(index);
}

void MinHeap::deleteMin()
{
    if(len == 0) return;

    arr[0][0] = arr[0][len-1];
    arr[1][0] = arr[1][len-1];
    arr[2][0] = arr[2][len-1];

    len--;

    siftDown(0);
}

void MinHeap::heapify(int * vertices1, int * vertices2, int * weight, int length)
{
    if(length > capacity) return;

    for(int i=0;i<length;i++)
    {
        arr[0][i] = weight[i];
        arr[1][i] = vertices1[i];
        arr[2][i] = vertices2[i];

        len++;

        siftUp(len - 1);
    }
}

void MinHeap::print()
{
    for(int i=0;i<len;i++)
    {
        cout<<arr[1][i]<<" "<<arr[2][i]<<" "<<arr[0][i]<<" "<<endl;
        //if(isPower(i+1)) cout<<"\n";                //to show each level differently
    }
    cout<<"\n";
}

MinHeap::~MinHeap()
{
    len = 0;
    delete[] arr[0];
    delete[] arr[1];
    delete[] arr[2];
}

class Arraylist
{
    int capacity;
    int * list;
    int length;

public:

    Arraylist()
    {
        list = new int[100];
        length = 0;
    }

    int getLength();
    void insertItem(int item);
    int getItemAt(int pos);
    void printList();
    ~Arraylist();

};

void Arraylist::insertItem(int item)
{
    list[length] = item ; //store new item
    length++ ;
	//printf("Item inserted.\n");
}

void Arraylist::printList()
{
        int i;
        for(i=0;i<length;i++)
        {
            cout<<list[i]<<" ";
        }

        cout<<endl;

}

int Arraylist::getItemAt(int pos)
{
    //cout<<"returned "<<list[pos]<<endl;
    return list[pos];
}

int Arraylist::getLength()
{
    //if(list == NULL) return 0;
    return length;
}

Arraylist::~Arraylist()
{
    delete list;
    length = 0;
}

class DisjointSet
{
    int n;
    int * parent;
    int * rank;

public:

    DisjointSet(int n)
    {
        this->n = n;

        parent = new int[n];
        rank = new int[n];

        for(int i=0;i<n;i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findParent(int x);
    void UnionSet(int x, int y);

    void print()
    {
        for(int i=0;i<n;i++)
        {
            cout<<i<<" "<<parent[i]<<" "<<rank[i]<<endl;
        }
    }

};


int DisjointSet::findParent(int x)
{
    if(x != parent[x])
    {
        return parent[x] = findParent(parent[x]);
    }

    else return x;
}

void DisjointSet::UnionSet(int x, int y)
{
    int px = findParent(x);
    int py = findParent(y);

    if(px == py) return;

    if(rank[px] < rank[py])
        parent[px] = py;

    else if(rank[px] > rank[py])
        parent[py] = px;

    else
    {
        parent[py] = px;
        rank[px]++;
    }
}

class Graph
{
    int vertices;

    int edges;

    int * firstNode;
    int * secondNode;
    int * weight;
    int index;

    //Arraylist ** adj;

public:

    Graph(int v, int e)
    {
        vertices = v;

        edges = e;

        //adj = new Arraylist*[2];
        //adj[0] = new Arraylist[vertices];
        //adj[1] = new Arraylist[vertices];

        firstNode = new int[edges];
        secondNode = new int[edges];
        weight = new int[edges];

        index = 0;
    }

    void addEdge(int u, int v, int w);
    void Kruskal();
    void Kruskal(int x);
};

void Graph::addEdge(int u, int v, int w)
{
    //adj[0][u].insertItem(v);
    //adj[1][u].insertItem(w);

    //adj[0][v].insertItem(u);
    //adj[1][v].insertItem(w);

    firstNode[index] = u;
    secondNode[index] = v;
    weight[index] = w;

    index++;

}


void Graph::Kruskal()
{
    int ind = 0, cost = 0;

    ofstream output;
    output.open("output.txt");

    MinHeap m(edges);

    m.heapify(firstNode, secondNode, weight, edges);

    cout<<endl;

    m.print();

    cout<<endl;

    DisjointSet d(vertices);

    while(!m.isEmpty())
    {
        int u = m.findMinEdgeFirstNode();
        int v = m.findMinEdgeSecondNode();
        int w = m.findMinEdge();

        //m.print();

        m.deleteMin();

        if(d.findParent(u) != d.findParent(v))
        {
            d.UnionSet(u, v);

            cout<<u<<" "<<v<<" "<<ind+1<<endl;
            output<<u<<" "<<v<<endl;

            cost += w;

            ind++;
        }

        if(ind >= vertices - 1) break;
    }

    cout<<cost;
    output<<cost;
}


void Graph::Kruskal(int x)
{
    int * taken = new int[vertices];

    for(int i=0;i<vertices;i++)
    {
        taken[i] = false;
    }

    MinHeap m(edges);

    m.heapify(firstNode, secondNode, weight, edges);

    cout<<endl;

    m.print();

    cout<<endl;

    int count = 0, cost = 0;

    while(count<vertices-1)
    {
        int u = m.findMinEdgeFirstNode();

        int v = m.findMinEdgeSecondNode();

        int w = m.findMinEdge();

        m.deleteMin();

        if(taken[u] && taken[v])
        {
            count++;
            continue;
        }

        else
        {
            cost += w;

            cout<<u<<" "<<v<<endl;

            taken[u] = taken[v] = true;
        }

        count++;
    }

    cout<<endl<<cost<<endl;

}
int main()
{
    ifstream input("input.txt");
    int n, e;
    //cin>>n>>e;
    input>>n>>e;

    Graph g(n, e);

    int u, v, w;

    for(int i=0;i<e;i++)
    {
        //cin>>u>>v>>w;
        input>>u>>v>>w;
        g.addEdge(u, v, w);
    }

    g.Kruskal();
    cout<<endl;
    //g.Kruskal(1);

    return 0;
}





















