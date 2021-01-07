#include<iostream>
#include<vector>

using namespace std;

class Graph
{
    int vertices;
    int ** mat;
    int * indegree;

public:

    Graph(int v);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void topsort();
};

Graph::Graph(int v)
{
    vertices = v;

    indegree = new int[vertices];

    mat = new int * [vertices];

    for(int i=0; i<vertices; i++)
    {
        mat[i] = new int[vertices];
    }

    for(int i=0; i<vertices; i++)
    {
        indegree[i] = 0;

        for(int j=0; j<vertices; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void Graph::addEdge(int u, int v)
{
    if(mat[u][v] == 1)
        return;

    mat[u][v] = 1;
    indegree[v]++;
}

void Graph::removeEdge(int u, int v)
{
    if(mat[u][v] == 0)
        return;

    mat[u][v] = 0;
    indegree[v]--;
}

void Graph::topsort()
{
    int count = 0;
    vector<int> result;

    bool * taken = new bool[vertices];

    for(int i=0; i<vertices; i++)
    {
        taken[i] = false;
    }

    while(count<vertices)
    {
        int temp = -1;

        for(int i=0; i<vertices; i++)
        {
            if(indegree[i] == 0 && taken[i] == false)
            {
                temp = i;
                taken[i] = true;

                break;
            }
        }

        for(int i=0; i<vertices; i++)
        {
            removeEdge(temp, i);
        }

        result.push_back(temp);

        count++;
    }

    for(int i=0; i<vertices; i++)
    {
        cout<<result[i]<<" ";
    }

    cout<<endl;
}

int main()
{
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topsort();

    return 0;
}
