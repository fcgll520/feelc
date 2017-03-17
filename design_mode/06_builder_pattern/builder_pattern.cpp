#include <stdio.h>

class Builder
{
public:
    virtual void BuildHead() {};
    virtual void BuildBoby() {};
};

class ThinBuilder : public Builder
{
public:
    void BuildHead()
    {
        printf("build thin head\n");
    }
    void BuildBoby()
    {
        printf("build thin boby\n");
    }
};

class FatBuilder : public Builder
{
public:
    void BuildHead()
    {
        printf("build fat head\n");
    }
    void BuildBoby()
    {
        printf("build fat boby\n");
    }
};

class Director
{
private:
    Builder *mBuilder;
public:
    Director(Builder *builder)
    {
        mBuilder = builder;
    }
    void create()
    {
        mBuilder->BuildHead();
        mBuilder->BuildBoby();
    }
};

int main()
{
    ThinBuilder thin;
    Director d(&thin);
    d.create();

    FatBuilder fat;
    Director d1(&fat);
    d1.create();
    return 0;
}