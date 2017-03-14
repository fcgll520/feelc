#include <stdio.h>
#include <assert.h>
enum CTYPE
{
    COREA,
    COREB,
};

class SingleCore
{
public:
    virtual void show() = 0;
};

class SingleCoreA : public SingleCore
{
public:
    void show() { printf("SingleCore A\n");
    }
};
class SingleCoreB : public SingleCore
{
public:
    void show()
    {
        printf("SingleCore B\n");
    }
};

class Factory
{
public:
    SingleCore* CreateSingleCore(enum CTYPE ctype)
    {
        if (ctype == COREA)
        {
            return new SingleCoreA();
        }
        else if (ctype == COREB)
        {
            return new SingleCoreB();
        }
        return NULL;
    }
};

int main()
{
    Factory f;
    SingleCore *pcore = f.CreateSingleCore(COREA);
    assert(pcore != NULL);
    pcore->show();

    pcore = f.CreateSingleCore(COREB);
    assert(pcore != NULL);
    pcore->show();


    return 0;
}

