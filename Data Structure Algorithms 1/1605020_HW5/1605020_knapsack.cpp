#include<iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    double * w;
    double * v;

    w = new double[n];
    v = new double[n];

    for(int i=0;i<n;i++)
    {
        cin>>w[i];
        cin>>v[i];
    }

    double cap;
    cin>>cap;

    int * index = new int[n];

    for(int i=0;i<n;i++)
    {
        index[i] = i+1;
    }

    double * ratio = new double[n];

    for(int i=0;i<n;i++)
    {
        ratio[i] = v[i] / w[i];
    }

    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(ratio[i] < ratio[j])
            {
                double temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = w[i];
                w[i] = w[j];
                w[j] = temp;

                temp = v[i];
                v[i] = v[j];
                v[j] = temp;

                int t = index[i];
                index[i] = index[j];
                index[j] = t;
            }
        }
    }

    double taken = 0.0;
    double value = 0.0;

    double d = 0;

    for(int i=0;i<n;i++)
    {

        if(taken + w[i] >= cap)
        {
            d = cap - taken;
            taken += d;
            value += d/w[i] * v[i];
            v[i] = d/w[i] * v[i];
            w[i] = d;
            break;
        }

        taken += w[i];
        value += v[i];

    }

    taken = 0;

    cout<<value<<endl;;

    for(int i=0;i<n;i++)
    {
        if(taken >= cap) break;
        cout<<index[i]<<" "<<w[i]<<" "<<v[i]<<endl;

        taken += w[i];
    }

    return 0;
}













