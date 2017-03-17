#include <stdio.h>

class Resume
{
protected:
    virtual void SetPersonalInfo() {}
    virtual void SetEducation() {}
    virtual void SetWorkExp() {}
public:
    void FillResume()
    {
        SetPersonalInfo();
        SetEducation();
        SetWorkExp();
    }
};

class ResumeA : public Resume
{
protected:
    void SetPersonalInfo()
    {
        printf("A's PersonalInfo\n");
    }
    void SetEducation()
    {
        printf("A's Education\n");
    }
    void SetWorkExp()
    {
        printf("A's WorkExp\n");
    }
};

class ResumeB : public Resume
{
protected:
    void SetPersonalInfo()
    {
        printf("B's PersonalInfo\n");
    }
    void SetEducation()
    {
        printf("B's Education\n");
    }
    void SetWorkExp()
    {
        printf("B's WorkExp\n");
    }
};

int main()
{
    Resume *r;
    r = new ResumeA();
    r->FillResume();
    delete r;

    r = new ResumeB();
    r->FillResume();
    delete r;
    r = NULL;
    
    return 0;
}
