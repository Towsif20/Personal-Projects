#include<iostream>
#include<fstream>

#define SIZE 500
#define NULL_VALUE INT_MIN

#define INF 99999
#define NIL -1

using namespace std;

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

    Graph(int V);

    void addEdge(int u, int v, int w);
    void BellmanFord(int source);
};

Graph::Graph(int v)
{
    vertices = v;
    adj = new Arraylist*[2];
    adj[0] = new Arraylist[vertices];
    adj[1] = new Arraylist[vertices];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[0][u].insertItem(v);
    adj[1][u].insertItem(w);
}

void Graph::BellmanFord(int source)
{
    int * dist = new int[vertices];

    int * prev = new int[vertices];

    for(int i=0;i<vertices;i++)
    {
        dist[i] = INF;
        prev[i] = NIL;
    }

    dist[source] = 0;

    int len, v, w;

    for(int i=0;i<vertices-1;i++)
    {
        for(int u=0;u<vertices;u++)
        {
            len = adj[0][u].getLength();

            for(int j=0;j<len;j++)
            {
                v = adj[0][u].getItemAt(j);
                w = adj[1][u].getItemAt(j);

                if(dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;

                    prev[v] = u;
                }
            }
        }
    }

    int * temp = new int[vertices];

    for(int i=0;i<vertices;i++)
    {
        temp[i] = dist[i];
    }

    for(int u=0;u<vertices;u++)
        {
            len = adj[0][u].getLength();

            for(int j=0;j<len;j++)
            {
                v = adj[0][u].getItemAt(j);
                w = adj[1][u].getItemAt(j);

                if(dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                }
            }
        }

    bool negcycle = false;

    for(int i=0;i<vertices;i++)
    {
        if(dist[i] != temp[i])
        {
            negcycle = true;
            break;
        }
    }

    //cout<<negcycle<<endl;

    if(negcycle == true)
    {
        cout<<"negative cycle exists. no shortest path available."<<endl;

        return;
    }

    ofstream output;
    output.open("output.txt");

    for(int i=0;i<vertices;i++)
    {
        output<<i<<" "<<dist[i]<<" "<<prev[i]<<endl;
        cout<<i<<" "<<dist[i]<<" "<<prev[i]<<endl;
    }

    output.close();
}

int main()
{
    ifstream input("input.txt");
    int n, e;
    input>>n>>e;

    Graph g(n);

    int u, v, w;

    for(int i=0;i<e;i++)
    {
        input>>u>>v>>w;
        g.addEdge(u, v, w);
    }

    int source;
    input>>source;

    g.BellmanFord(source);

    input.close();

}


