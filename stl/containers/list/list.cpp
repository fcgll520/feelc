#include <iostream>
#include <list>
#include <iomanip>
using namespace std;
int main()
{
    // 有序数据 
    int A1[]={1,2,3,4,5,6};
    int A2[]={2,4,6,8,9,10};
    
    // 无序数据
    int A3[]={1,2,3,4,6,9};
    int A4[]={5,6,7,8,9,2};
    
    //有序链表 
    list<int> iL1(A1, A1+6);
    list<int> iL2(A2, A2+6);
    
    //无序链表
    list<int> iL3(A3, A3+6);
    list<int> iL4(A4, A4+6);
    
    iL1.merge(iL2);
    iL3.merge(iL4);
    
    list<int>::iterator it = iL1.begin();
    
    while(it!=iL1.end())
    {
        cout<<setw(3)<<*it++;
    }
    cout<<endl;
    it=iL3.begin();
    while(it!=iL3.end())
    {
        cout<<setw(3)<<*it++;
    }    
    cout<<endl;
    
    return 0;

}
