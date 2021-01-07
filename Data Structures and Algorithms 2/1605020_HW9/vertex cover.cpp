#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<fstream>

using namespace std;

class Graph
{
    int vertices;
    vector<int> * adjlist;

public:

    Graph(int V);
    void addEdge(int u, int v);
    int vertexCover();

};

Graph::Graph(int V)
{
    vertices = V;

    adjlist = new vector<int>[vertices];
}

void Graph::addEdge(int u, int v)
{
    adjlist[u].push_back(v);
    adjlist[v].push_back(u);
}

int Graph::vertexCover()
{
    bool * visited = new bool[vertices];
    bool * alreadyTakenU = new bool[vertices];

    for(int i=0; i<vertices; i++)
    {
        visited[i] = false;
        alreadyTakenU[i] = false;
    }

    int count = 0;

    while(count < vertices)
    {
        srand(time(0));

        int u = rand() % vertices;

        while(alreadyTakenU[u])
        {
            u = rand() % vertices;
        }

        alreadyTakenU[u] = true;

        if(visited[u] == false)
        {
            int t = 0;
            int len = adjlist[u].size();

            bool * alreadyTakenV = new bool[len];

            for(int i=0; i<len; i++)
            {
                alreadyTakenV[i] = false;
            }

            while(t < len)
            {
                srand(time(0));

                int v = rand() % len;

                while(alreadyTakenV[v])
                {
                    v = rand() % len;
                }

                alreadyTakenV[v] = true;

                v = adjlist[u][v];

                t++;

                if(visited[v] == false)
                {
                    visited[u] = true;
                    visited[v] = true;

                    //cout<<u<<" "<<v<<endl;

                    break;
                }
            }


        }

        //cout<<count<<" "<<u<<endl;

        count++;

    }

    count = 0;

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
