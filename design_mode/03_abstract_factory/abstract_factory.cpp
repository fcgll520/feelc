#include <stdio.h>
#include <assert.h>


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

class MultiCore
{
public:
    virtual void show() = 0;
};

class MultiCoreA : public MultiCore
{
public:
    void show()
    {
        printf("MultiCore A\n");
    }
};

class MultiCoreB : public MultiCore
{
public:
    void show()
    {
        printf("MultiCore B\n");
    }
};
class Factory
{
public:
    virtual SingleCore* CreateSingleCore() = 0;
    virtual MultiCore* CreateMultiCore() = 0;
};

class FactoryA : public Factory
{
public:
    SingleCore* CreateSingleCore()
    {
        return new SingleCoreA();
    }
    MultiCore* CreateMultiCore()
    {
        return new MultiCoreA();
    }
};

class FactoryB : public Factory
{
public:
    SingleCore* CreateSingleCore()
    {
        return new SingleCoreB();
    }
    MultiCore* CreateMultiCore()
    {
        return new MultiCoreB();
    }
};

int main()
{
    FactoryA fa;
    SingleCore *psingle_core = fa.CreateSingleCore();
    assert(psingle_core != NULL);
    psingle_core->show();

    MultiCore *pmulti_core = fa.CreateMultiCore();
    assert(pmulti_core != NULL);
    pmulti_core->show();

    FactoryB fb;
    psingle_core = fb.CreateSingleCore();
    assert(psingle_core != NULL);
    psingle_core->show();

    pmulti_core = fb.CreateMultiCore();
    assert(pmulti_core != NULL);
    pmulti_core->show();

    return 0;
}

