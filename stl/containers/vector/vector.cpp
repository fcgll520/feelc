#include <stdio.h>
#include <vector>
#include <algorithm>
using std::vector;

void display(vector<int> &iv)
{
    int i = 0;
    int size = iv.size();

    for (i = 0; i < size; i++)
    {
        printf("%d ", iv[i]);
    }
    printf("\n");
}

int main()
{   
    vector<int> iv(2, 9);

    printf("size: %d\n", iv.size());
    printf("capcaity: %d\n", iv.capacity());

    iv.push_back(0);
    iv.push_back(1);
    iv.push_back(2);
    iv.push_back(3);
    iv.push_back(4);
    iv.push_back(5);
    iv.push_back(6);
    iv.push_back(7);

    display(iv);

    iv.pop_back();
    iv.pop_back();
    display(iv);

    vector<int>::iterator  iviter = find(iv.begin(), iv.end(), 2);
    if (iviter != iv.end())
    {
        iv.erase(iviter);
    }
    display(iv);

    iviter = find(iv.begin(), iv.end(), 4);
    if (iviter != iv.end())
    {
        iv.insert(iviter, 2, 20);
    }
    display(iv);

    for (iviter = iv.begin(); iviter != iv.end();)
    {
        if (*iviter % 2 == 0)
        {
            iviter = iv.erase(iviter);
        }
        else
        {
            iviter++;
        }
    }
    display(iv);
    
    
    return 0;
}
