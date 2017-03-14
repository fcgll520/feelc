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
    virtual SingleCore* CreateSingleCore() = 0;
};

class FactoryA : public Factory
{
public:
    SingleCore* CreateSingleCore()
    {
        return new SingleCoreA();
    }
};

class FactoryB : public Factory
{
public:
    SingleCore* CreateSingleCore()
    {
        return new SingleCoreB();
    }
};

int main()
{
    FactoryA fa;
    SingleCore *pcore = fa.CreateSingleCore();
    assert(pcore != NULL);
    pcore->show();

    FactoryB fb;
    pcore = fb.CreateSingleCore();
    assert(pcore != NULL);
    pcore->show();


    return 0;
}

