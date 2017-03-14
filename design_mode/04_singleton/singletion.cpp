#include <stdio.h>

class Singletion
{
public:
    static Singletion* GetInstance()
    {
        if (instance == NULL)
        {
            instance = new Singletion();
        }
        return instance;
    }
private:
    Singletion() {};
    static Singletion *instance;
};

Singletion* Singletion::instance = NULL;

int main()
{
    Singletion *s1 = Singletion::GetInstance();
    Singletion *s2 = Singletion::GetInstance();

    printf("s1: %p\n", s1);
    printf("s2: %p\n", s2);

    return 0;
}
