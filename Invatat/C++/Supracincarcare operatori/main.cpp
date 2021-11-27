#include <iostream>
#include<cstdlib
#include<new>

using namespace std;
class atype{
    int a[3];
public:
    atype(int i, int j, int k){a[0]=i; a[1]=j; a[2]=k}
    int &operator[]{return a[i];}
};

int main()
{
    atype ob(1, 2,3);
    cout<< ob[1];
    cout<<" ";
    ob[1]=25;
    cout<<ob[1];
    return 0;
}
