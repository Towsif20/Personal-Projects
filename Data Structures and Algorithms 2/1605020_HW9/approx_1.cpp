#include<bits/stdc++.h>
using namespace std;

class Graph
{
    int nVertices,nEdges;
    vector<int> *adjList;
public:
    Graph(int a,int b)
    {
        nVertices=a;
        nEdges=b;
        adjList=new vector<int>[a];
    }

    void addEdge(int u,int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int getDegree(int u)
    {
        return adjList[u].size();
    }

    void removeEdge(int u,int v)
    {
        for(vector<int>::iterator iter = adjList[u].begin(); iter != adjList[u].end(); ++iter )
        {
            if(*iter == v)
            {
                adjList[u].erase( iter );
                break;
            }
        }
        for(vector<int>::iterator iter = adjList[v].begin(); iter != adjList[v].end(); ++iter )
        {
            if(*iter == u)
            {
                adjList[v].erase( iter );
                break;
            }
        }
        nEdges--;
    }

    int vertexCover()
    {
        bool *vertexCover=new bool[nVertices];
        bool *marked=new bool[nVertices];

        for(int i=0; i<nVertices; i++)
        {
            vertexCover[i]=false;
            marked[i]=false;
        }

        int c = 0;

        while(c < nVertices)
        {
            int u,v;
            u=rand()% nVertices;
            while(marked[u])
            {
                u=rand()% nVertices;
            }
            marked[u]=true;

            if(!vertexCover[u])
            {
                int len = adjList[u].size();

                int t = 0;

                bool * temp = new bool[len];

                for(int i=0; i<adjList[u].size(); i++)
                    temp[i] = false;

                while(t < len)
                {
                    v=rand()% len;



                    while(temp[v])
                    {
                        v = rand()%adjList[u].size();
                    }

                    temp[v] = true;

                    v=adjList[u][v];

                    if(!vertexCover[v])

                    {
                        //nEdges-=adjList[u].size();
                        //nEdges-=adjList[v].size();
                        //adjList[u].clear();
                        //adjList[v].clear();
                        vertexCover[u]=true;
                        vertexCover[v]=true;
                        break;
                    }

                    t++;

                }



            }

            c++;
        }
        int cnt=0;
        for(int i=0; i<nVertices; i++)
        {
            if(vertexCover[i]) cnt++;
        }
        return cnt;
    }

    void print()
    {
        for(int i=0; i<nVertices; i++)
        {
            cout<<i<<" : ";
            for(int j=0; j<adjList[i].size(); j++)
            {
                cout<<adjList[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
int main()
{
    int n,e;
    freopen("test case 1.txt","r",stdin);
    cin>>n>>e;
    Graph g1(n,e);
    int u,v;
    for(int i=0; i<e; i++)
    {
        char a;
        cin>>a;
        cin>>u>>v;
        g1.addEdge(u-1,v-1);
    }

    cout<<g1.vertexCover()<<endl;



}
