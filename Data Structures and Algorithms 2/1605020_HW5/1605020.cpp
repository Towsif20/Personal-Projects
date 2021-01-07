#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>

#define NULL_VALUE -999999
#define INFINITY 999999

#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices;
	int ** matrix ;
	int * parent;
	bool * visited;
	int ** flow;

	int src;
	int sink;

public:
	Graph(int n, int s, int t);
	~Graph();
	int ** getMatrix()
	{
	     return matrix;
    }

	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
	void bfs(int source);
	int maxflow();
	void mincuct(Graph t);
};


Graph::Graph(int n, int source, int terminal)
{
	nVertices = n ;

    matrix = new int*[nVertices];
    flow = new int*[nVertices];

    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        flow[i] = new int[nVertices];

        for(int j=0;j<nVertices;j++)
           {
                matrix[i][j] = 0;
                flow[i][j] = 0;
           }
    }

    parent = new int[nVertices];
    visited = new bool[nVertices];

    src = source;

    sink = terminal;
}

void Graph::addEdge(int u, int v, int w)
{
    matrix[u][v] = w;
}

void Graph::removeEdge(int u, int v)
{
    matrix[u][v] = 0;
}

bool Graph::isEdge(int u, int v)
{
    return matrix[u][v] != 0;
}

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        parent[i] = -1 ;
        visited[i] = false;
    }

    Queue q ;

    visited[src] = true;

    q.enqueue(source) ;

    while( !q.empty() )
    {
        int u = q.dequeue();

        for(int v=0;v<nVertices;v++)
        {
            if(matrix[u][v] > 0 && visited[v] == false)
            {

                parent[v] = u;

                q.enqueue(v);

                visited[v] = true;
            }
        }
    }

}

int Graph::maxflow()
{
    ofstream output;
    output.open("output.txt");

    int max_flow = 0;

    this->bfs(src);

    bool b = visited[sink];

    int path_flow, p, q;

    while(b == true)
    {
        path_flow = INT_MAX;

        int v = sink;

        while(v != src)
        {
            int u = parent[v];

            if(path_flow > matrix[u][v])
            {
                path_flow = matrix[u][v];
                p = u, q = v;
            }

            v = parent[v];

        }

        //cout<<p<<" "<<q<<" "<<path_flow<<endl;

        //output<<p<<" "<<q<<" "<<path_flow<<endl;

        v = sink;

        while(v != src)
        {
            int u = parent[v];

            matrix[u][v] -= path_flow;
            matrix[v][u] += path_flow;

            flow[u][v] += path_flow;


            v = parent[v];

        }

        bfs(src);

        b = visited[sink];

        max_flow += path_flow;
    }

    cout<<endl;
    output<<endl;

    for(int u=0;u<nVertices;u++)
    {
        for(int v=0;v<nVertices;v++)
        {
            cout<<flow[u][v]<<" ";
            output<<flow[u][v]<<" ";
        }
        cout<<endl;
        output<<endl;
    }

    cout<<endl<<max_flow<<endl;
    output<<endl<<max_flow<<endl;

    output.close();

    return max_flow;

}

void Graph::mincuct(Graph t)
{
    ofstream output;
    output.open("outputmincut.txt");

    this->bfs(src);

    int ** mat = t.getMatrix();

    for (int i = 0; i < nVertices; i++)
    {
        for (int j = 0; j < nVertices; j++)
        {
            if (visited[i] && !visited[j] && mat[i][j])
            {
                cout << i << " " << j <<" "<< mat[i][j]<<endl;
                output<< i << " " << j <<" "<< mat[i][j]<<endl;
            }

        }

    }

    output.close();

}

Graph::~Graph()
{
    if(matrix)
    {
        for(int i=0;i<nVertices;i++)
        {
            delete [] matrix[i];
            matrix[i] = 0;
        }

        delete [] matrix;
        matrix = 0;
    }

    if(parent) delete [] parent;
    parent = 0;
}

int main()
{
    ifstream input("input.txt");
    int n, e, s, t;
    //cin>>n>>e;
    input>>n>>e>>s>>t;

    Graph g(n, s, t);
    Graph g2(n, s, t);

    int u, v, w;

    for(int i=0;i<e;i++)
    {
        //cin>>u>>v>>w;
        input>>u>>v>>w;

        g.addEdge(u, v, w);
        g2.addEdge(u, v, w);
    }
/*
      g.addEdge(0, 1, 3 );
      g.addEdge(0, 2, 7 ) ;
      g.addEdge(1, 3, 9);
      g.addEdge(1, 4, 9 );
      g.addEdge(2, 1, 9 );
      g.addEdge(2, 4, 9);
      g.addEdge(2, 5, 4);
      g.addEdge(3, 5, 3);
      g.addEdge(4, 5, 7 );
      g.addEdge(0, 4, 10);
      */

    g.maxflow();

    g.mincuct(g2);

    return 0;
}


