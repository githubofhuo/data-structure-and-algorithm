#include <iostream>
#include "BigNum1.h"
using namespace std;

int main() {
//    int i,n;
//    BigNum x[101];      //定义大数的对象数组
//    x[0]=1;
//    for(i=1;i<101;i++)
//        x[i]=x[i-1]*(4*i-2)/(i+1);
//    cin>>n;
//    x[n].print();
//    x[n+1].print();
//    (x[n]+x[n+1]).print();
//    (x[n]-x[n+1]).print();
//    (x[n]*x[n+1]).print();
//    (x[n]/100).print();
//    (x[n]^20).print();
//    cout<<x[n]%100<<endl;
    BigNum b(2);
    (b^100).print();
    return 0;
}