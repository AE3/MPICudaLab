#include <iostream>
#include "master.h"

using namespace std;

int main()
{
    int* a= new int[10];
    for (int i=0;i<10;i++){
        a[i]=2;
    }
    Master master(a,10,4);
    cout << "Hello World!" << endl;
    return 0;
}

