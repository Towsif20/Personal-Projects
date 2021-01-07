#include<iostream>

using namespace std;

int powerMod(int n)
{
    int p = 1;

    for(int i=0;i<n;i++)
    {
        p = p*n;

        if(p>10) p = p%10;
    }

    return p;
}

int main()
{
    //cout<<powerMod(2020);

    int sum = 0;

    int n = 2020;

    for(int i=1;i<=n;i++)
    {
        sum += powerMod(i);

        if(sum>0) sum = sum%10;
    }

    cout<<sum;

    return 0;
}
