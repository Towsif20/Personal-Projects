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

    int getVertex(int i){ return arr[0][i]; }
    int getWeight(int i){ return arr[1][i]; }


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

    int leftChildVertex(int i)
    {
        if(hasLeftChild(i)) return arr[0][2*i + 1];

        else return INT_MAX;
    }

    int leftChildWeight(int i)
    {
        if(hasLeftChild(i)) return arr[1][2*i + 1];

        else return INT_MAX;
    }

    int rightChildVertex(int i)
    {
        if(hasRightChild(i)) return arr[0][2*i + 2];

        else return INT_MAX;
    }

    int rightChildWeight(int i)
    {
        if(hasRightChild(i)) return arr[1][2*i + 2];

        else return INT_MAX;
    }

    int parentVertex(int i)
    {
       if(hasParent(i)) return arr[0][(i-1)/2];
    }

    int parentWeight(int i)
    {
       if(hasParent(i)) return arr[1][(i-1)/2];
    }

    MinHeap(int cap);
    int findMinVertex();
    int findMinWeight();
    void insert(int vertex, int weight);
    int extractMinVertex();
    int extractMinWeight();
    void deleteMin();
    void replace(int item);
    void heapify(int * vertices, int * weight, int length);
    int size();
    bool isEmpty();
    void decreaseKey(int old, int val, int i);
    void deleteItemAt(int pos);
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
    arr = new int*[2];
    arr[0] = new int[capacity];
    arr[1] = new int[capacity];
}

int MinHeap::size()
{
    return len;
}

bool MinHeap::isEmpty()
{
    return len == 0;
}

int MinHeap::findMinVertex()
{
    if(len == 0) return INT_MAX;

    return arr[0][0];
}

int MinHeap::findMinWeight()
{
    if(len == 0) return INT_MAX;

    return arr[1][0];
}

void MinHeap::siftDown(int i)
{
  int left = leftChildIndex(i);
  int right = rightChildIndex(i);

  int smallest = i;

  if(left<len && arr[1][left] < arr[1][smallest])
    smallest = left;

  if(right<len && arr[1][right] < arr[1][smallest])
    smallest = right;

  if(smallest != i)
  {
      swap(arr[0][smallest], arr[0][i]);
      swap(arr[1][smallest], arr[1][i]);
      siftDown(smallest);
  }
}

void MinHeap::siftUp(int i)
{
    if(i && arr[1][parentIndex(i)] > arr[1][i])
    {
        swap(arr[0][i], arr[0][parentIndex(i)]);
        swap(arr[1][i], arr[1][parentIndex(i)]);

        siftUp(parentIndex(i));
    }
}

void MinHeap::insert(int vertex, int weight)
{
    if(len == capacity) return;

    arr[0][len] = vertex;
    arr[1][len] = weight;
    len++;
    int index = len-1;

    siftUp(index);
}

int MinHeap::extractMinVertex()
{
    if(len == 0) return INT_MIN;

    int t = arr[0][0];
    deleteMin();

    return t;
}

int MinHeap::extractMinWeight()
{
    if(len == 0) return INT_MIN;

    int t = arr[1][0];
    deleteMin();

    return t;
}

void MinHeap::deleteMin()
{
    if(len == 0) return;

    arr[1][0] = arr[1][len-1];
    arr[0][0] = arr[0][len-1];
    len--;

    siftDown(0);
}


void MinHeap::heapify(int * vertices, int * weight, int length)
{
    if(length > capacity) return;

    for(int i=0;i<length;i++)
    {
        arr[0][i] = vertices[i];
        arr[1][i] = weight[i];
        len++;

        siftUp(len - 1);
    }
}



void MinHeap::deleteItem(int item)
{
    int t = -1;
    for(int i=0;i<len;i++)
    {
        if(arr[1][i] == item)
        {
            t = i;
            break;
        }
    }

    if(t == -1) return;

    arr[1][t] = arr[1][len-1];
    arr[0][t] = arr[0][len-1];

    len--;

    siftDown(0);

}


void MinHeap::decreaseKey(int old, int val, int v)
{
    deleteItem(old);
    insert(v, val);
}

void MinHeap::print()
{
    for(int i=0;i<len;i++)
    {
        cout<<arr[0][i]<<" "<<arr[1][i]<<endl;
        //if(isPower(i+1)) cout<<"\n";                //to show each level differently
    }
    cout<<"\n";
}

MinHeap::~MinHeap()
{
    len = 0;
    delete[] arr[0];
    delete[] arr[1];
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


class Graph
{
    int vertices;

    Arraylist ** adj;

public:
    Graph(int V)
    {
        vertices = V;
        adj = new Arraylist*[2];
        adj[0] = new Arraylist[vertices];
        adj[1] = new Arraylist[vertices];
    }

    void addEdge(int u, int v, int w);
    void dijkstra(int source);
    void print();
};

void Graph::addEdge(int u, int v, int w)
{
    adj[0][u].insertItem(v);
    adj[1][u].insertItem(w);

    //adj[0][u].printList();
    //adj[1][u].printList();

}

void Graph::print()
{
    for(int i=0;i<vertices;i++)
    {
        adj[0][i].printList();
        adj[0][i].printList();
    }
}

void Graph::dijkstra(int source)
{
    int * dist = new int[vertices];
    int * prev = new int[vertices];
    int * nodes = new int[vertices];

    for(int i=0;i<vertices;i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
        nodes[i] = i;
    }

    dist[source] = 0;

    MinHeap m(100);

    m.heapify(nodes, dist, vertices);

    //m.print();

    int u, v, l, w;

    while(!m.isEmpty())
    {
        u = m.extractMinVertex();

        l = adj[0][u].getLength();

        //adj[0][u].printList();

        //adj[1][u].printList();

        for(int j=0;j<l;j++)
        {
            v = adj[0][u].getItemAt(j);

            w = adj[1][u].getItemAt(j);

            //cout<<v<<" "<<w<<endl;

            if(dist[v] > dist[u] + w)
            {
                int t = dist[v];
                dist[v] = dist[u] + w;

                prev[v] = u;

                //m.deleteItem(t);
                //m.insert(v, dist[v]);
                m.decreaseKey(t, dist[v], v);

                //m.print();
            }
        }
    }

    cout<<endl;

    ofstream output;
    output.open("output.txt");

    for(int i=0;i<vertices;i++)
    {
        cout<<i<<" "<<dist[i]<<" "<<prev[i]<<endl;
        output<<i<<" "<<dist[i]<<" "<<prev[i]<<endl;
    }

    output.close();
}

int main()
{
    ifstream input("test case.txt");
    int n, e;
    input>>n>>e;
    //cout<<n<<" "<<e<<endl;

    Graph g(n);

    int u, v, w;

    for(int i=0;i<e;i++)
    {
        input>>u>>v>>w;
        //cout<<u<<" "<<v<<" "<<w<<endl;
        g.addEdge(u, v, w);
    }
    int source;
    input>>source;
    //cout<<source;

    g.dijkstra(source);

    input.close();

}


