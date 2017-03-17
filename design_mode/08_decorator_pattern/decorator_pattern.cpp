#include <stdio.h>
#include <string>

using std::string;

class Phone
{
public:
    Phone() {}
    virtual ~Phone() {}
    virtual void ShowDecorate() {}
};

class NokiaPhone : public Phone
{
public:
    NokiaPhone(string name) : m_name(name)
    {}
    ~NokiaPhone() {}
    void ShowDecorate()
    {
        printf("NokiaPhone::ShowDecorate: %s\n", m_name.c_str());
    }
private:
    string  m_name;
};

class IPhone : public Phone
{
public:
    IPhone() {}
    ~IPhone() {}
    void ShowDecorate()
    {
        printf("IPhone::ShowDecorate: %s\n", m_name.c_str());
    }
private:
    string  m_name;
};

class DecorateorPhone : public Phone
{
public:
    DecorateorPhone(Phone *phone)
    {
        m_phone = phone;
    }
    virtual void ShowDecorate()
    {
        m_phone->ShowDecorate();
    }
private:
    Phone *m_phone;
};

class DecoratorPhoneA : public DecorateorPhone
{
public:
    DecoratorPhoneA(Phone *phone) : DecorateorPhone(phone)
    {
    }
    void ShowDecorate()
    {
        DecorateorPhone::ShowDecorate();
        AddDecorate();
    }
private:
    void AddDecorate()
    {
        printf("AddDecorate ***A\n");
    }
};

class DecoratorPhoneB : public DecorateorPhone
{
public:
    DecoratorPhoneB(Phone *phone) : DecorateorPhone(phone)
    {
    }
    void ShowDecorate()
    {
        DecorateorPhone::ShowDecorate();
        AddDecorate();
    }
private:
    void AddDecorate()
    {
        printf("AddDecorate ---B\n");
    }
};

int main()
{
    Phone *nokiaPhone = new NokiaPhone("nokia");
    Phone *dpa = new DecoratorPhoneA(nokiaPhone);
    Phone *dpb = new DecoratorPhoneB(dpa);

    dpa->ShowDecorate();
    dpb->ShowDecorate();

    delete dpa;
    delete dpb;
    delete nokiaPhone;
    return 0;
}