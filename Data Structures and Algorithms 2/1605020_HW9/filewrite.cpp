#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    ofstream output;
    output.open("worst.txt");

    output<<400<<" "<<200<<endl;

    for(int i=1;i<=200;i++)
    {
        output<<i<<" "<<400-i+1<<endl;
    }

    output.close();

    return 0;
}
