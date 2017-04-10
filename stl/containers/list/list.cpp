#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int i;
    vector<int> iv(2, 9);
    printf("size: %d\n", iv.size());
    printf("capacity=%d\n", iv.capacity());

    iv.push_back(1);
    printf("size: %d\n", iv.size());
    printf("capacity=%d\n", iv.capacity());

    iv.push_back(2);
    printf("size: %d\n", iv.size());
    printf("capacity=%d\n", iv.capacity());
    
    iv.push_back(3);
    printf("size: %d\n", iv.size());
    printf("capacity=%d\n", iv.capacity());
    
    iv.push_back(4);
    printf("size: %d\n", iv.size());
    printf("capacity=%d\n", iv.capacity());

    iv.push_back(5);
    printf("size=%d\n", iv.size());
    printf("capacity: %d\n", iv.capacity());
    for (i = 0; i < iv.size(); ++i)
    {
        printf("%d  ", iv[i]);
    }
    printf("\n");

    iv.pop_back();
    iv.pop_back();
    printf("size: %d\n", iv.size());
    printf("capacity: %d\n", iv.capacity());
    
    iv.pop_back();
    printf("size: %d\n", iv.size());
    printf("capacity: %d\n", iv.capacity());

    vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
    if (ivite != iv.end())
    {
        iv.erase(ivite);
    }

    printf("size: %d\n", iv.size());
    printf("capacity: %d\n", iv.capacity());

    for (i = 0; i < iv.size(); i++)
    {
        printf("%d  ", iv[i]);
    }
    printf("\n");

    return 0;
}
