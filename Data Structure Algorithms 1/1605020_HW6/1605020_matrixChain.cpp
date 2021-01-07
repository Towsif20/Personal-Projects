#include<iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int * p = new int[n];
    int ** m;
    m = new int * [n];

    for(int i=0; i<n; i++)
    {
        m[i] = new int[n];
    }

    for(int i=0; i<n; i++)
    {
        cin>>p[i];
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            m[i][j] = 0;
        }
    }

    for (int d=1; d<n-1; d++)
    {
        for (int i=1; i<n-d; i++)
        {
            int j = i + d;
            m[i][j] = INT_MAX;

            for (int k=i; k<=j-1; k++)
            {
                int x = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (x < m[i][j])
                {
                    m[i][j] = x;
                }
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        delete[] m[i];
    }

    //delete[][] L;

    delete[] p;

    cout<<m[1][n-1];

    return 0;
}

