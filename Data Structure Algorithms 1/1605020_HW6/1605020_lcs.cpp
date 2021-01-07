#include<iostream>
#include<cstring>
#include<stack>

using namespace std;

int main()
{
    string A, B;

    cin>>A>>B;

    int lenA = A.length();
    int lenB = B.length();

    for(int i=0;i<lenA;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;

    for(int i=0;i<lenB;i++)
    {
        cout<<B[i]<<" ";
    }
    cout<<endl;

    int ** arr = new int * [lenA+1];

    for(int i=0;i<=lenA;i++)
    {
        arr[i] = new int[lenB+1];
    }

    for(int i=0;i<=lenA;i++)
    {
        for(int j=0;j<=lenB;j++)
        {
            if(i==0 || j==0)    arr[i][j] = 0;

            else if(A[i-1] == B[j-1])   arr[i][j] = 1 + arr[i-1][j-1];

            else    arr[i][j] = max(arr[i-1][j], arr[i][j-1]);
        }
    }

    for(int i=0;i<=lenA;i++)
    {
        for(int j=0;j<=lenB;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<arr[lenA][lenB]<<endl;

    stack<char> st;

    int i = lenA, j = lenB;

    while(i>0 && j>0)
    {

        if(A[i-1] == B[j-1])
        {
            cout<<A[i-1]<<" "<<B[j-1]<<endl;
            st.push(B[j-1]);
            i--;
            j--;
        }

        else if(arr[i-1][j] > arr[i][j-1]) i--;

        else j--;
    }

    cout<<endl;

    while(!st.empty())
    {
        cout<<st.top();
        st.pop();
    }

    return 0;
}
