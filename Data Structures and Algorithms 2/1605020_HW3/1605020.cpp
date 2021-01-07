#include<iostream>
#include<fstream>

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
    void floydwarshall();
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

void Graph::floydwarshall()
{
    int ** dist;
    int ** pred;
    dist = new int*[vertices];
    pred = new int*[vertices];

    ofstream output;
    output.open("output.txt");

    for(int i=0;i<vertices;i++)
    {
        dist[i] = new int[vertices];

        pred[i] = new int[vertices];
    }

    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
        {
            if(i == j) dist[i][j] = 0;

            else dist[i][j] = INF;

            pred[i][j] = NIL;
        }
    }

    int len, v, w;

   for(int u=0;u<vertices;u++)
   {
       len = adj[0][u].getLength();

       for(int i=0;i<len;i++)
       {
           v = adj[0][u].getItemAt(i);
           w = adj[1][u].getItemAt(i);

           dist[u][v] = w;
           pred[u][v] = u;
       }
   }

   for(int k=0;k<vertices;k++)
   {
       for(int i=0;i<vertices;i++)
       {
           for(int j=0;j<vertices;j++)
           {
               if(dist[i][j] > dist[i][k] + dist[k][j])
               {
                   dist[i][j] = dist[i][k] + dist[k][j];

                   pred[i][j] = pred[k][j];
               }
           }
       }
   }

   bool negcycle = false;

   for(int i=0;i<vertices;i++)
   {
       if(dist[i][i] < 0)
       {
           negcycle = true;
           break;
       }
   }

   if(negcycle)
   {
       cout<<"negative cycle: yes"<<endl;
       output<<"negative cycle: yes"<<endl;

       return;
   }

   cout<<endl;
   output<<endl;

   cout<<"distance matrix: "<<endl<<endl;

   output<<"distance matrix: "<<endl<<endl;

   for(int i=0;i<vertices;i++)
    {
        cout<<i+1<<"     ";
        output<<i+1<<"     ";
        for(int j=0;j<vertices;j++)
        {

            cout<<dist[i][j]<<" ";

            output<<dist[i][j]<<" ";
        }

        cout<<endl;

        output<<endl;
    }

    cout<<endl;
    output<<endl;

    cout<<"predecessor matrix: "<<endl<<endl;

    output<<"predecessor matrix: "<<endl<<endl;

    for(int i=0;i<vertices;i++)
    {
        cout<<i+1<<"     ";

        output<<i+1<<"     ";

        for(int j=0;j<vertices;j++)
        {

            cout<<pred[i][j] + 1<<" ";

            output<<pred[i][j] + 1<<" ";
        }

        cout<<endl;

        output<<endl;
    }

    cout<<endl;

    output<<endl;

    cout<<"negative cycle: no"<<endl;

    output<<"negative cycle: no"<<endl;

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
        g.addEdge(u-1, v-1, w);
    }

    g.floydwarshall();

    input.close();
}










