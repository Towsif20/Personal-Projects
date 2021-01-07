#include<iostream>
#include<fstream>

using namespace std;

class Graph
{
    int vertices;
    int edges;
    int ** mat;
    int * deg;

public:

    Graph(int V);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);

    int vertexCover();
};

Graph::Graph(int V)
{
    vertices = V;

    edges = 0;

    mat = new int*[vertices];

    deg = new int[vertices];

    for(int i=0;i<vertices;i++)
    {
        mat[i] = new int[vertices];

        deg[i] = 0;
    }

    for(int i=0;i<vertices;i++)
    {
        for(int j=0;j<vertices;j++)
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
    mat[v][u] = 1;

    edges++;

    deg[u]++;

    deg[v]++;
}

void Graph::removeEdge(int u, int v)
{
    if(mat[u][v] == 0)
        return;

    mat[u][v] = 0;
    mat[v][u] = 0;

    edges--;

    deg[u]--;

    deg[v]--;
}

int Graph::vertexCover()
{
    bool * visited = new bool[vertices];

    for(int i=0;i<vertices;i++)
    {
        visited[i] = false;
    }

    int p, q;

    while(edges > 0)
    {
        int max = INT_MIN;

        for(int u=0;u<vertices;u++)
        {
            for(int v=0;v<vertices;v++)
            {
                if(mat[u][v] == 1)
                {
                    if(deg[u] + deg[v] > max)
                    {
                        max = deg[u] + deg[v];

                        p = u, q = v;
                    }
                }
            }
        }

        for(int i=0;i<vertices;i++)
        {
            removeEdge(p, i);
            removeEdge(q, i);

            visited[p] = visited[q] = true;

            //cout<<p<<" "<<q<<endl;
        }
    }

    int count = 0;

    for(int i=0;i<vertices;i++)
    {
        if(visited[i])
            count++;
    }

    return count;
}

int main()
{
        ifstream input("test case 1.txt");

    int n, e;
    input>>n>>e;

    Graph g(n);

    for(int i=0;i<e;i++)
    {
        int u, v;
        char c;

        input>>c>>u>>v;

        g.addEdge(u-1, v-1);
    }

    /*
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    //g.addEdge(2, 3);

    */
    input.close();
    cout<<g.vertexCover()<<endl;

    input.open("test case 2.txt");

    input>>n>>e;

    Graph g2(n);

    for(int i=0;i<e;i++)
    {
        int u, v;
        char c;

        input>>c>>u>>v;

        g2.addEdge(u-1, v-1);
    }


    input.close();

    cout<<g2.vertexCover()<<endl;

    input.open("test case 3.txt");

    input>>n>>e;

    Graph g3(n);

    for(int i=0;i<e;i++)
    {
        int u, v;
        char c;

        input>>c>>u>>v;

        g3.addEdge(u-1, v-1);
    }


    input.close();

    cout<<g3.vertexCover()<<endl;

    input.open("test case 4.txt");

    input>>n>>e;

    Graph g4(n);

    for(int i=0;i<e;i++)
    {
        int u, v;
        char c;

        input>>c>>u>>v;

        g4.addEdge(u-1, v-1);
    }


    input.close();
    cout<<g4.vertexCover()<<endl;




    input.open("worst.txt");

    input>>n>>e;

    Graph g5(n);

    for(int i=0;i<e;i++)
    {
        int u, v;

        input>>u>>v;

        g5.addEdge(u-1, v-1);
    }


    input.close();
    cout<<g5.vertexCover()<<endl;

    return 0;


}
