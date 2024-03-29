#include "lm.helloworld.pb.h"
void ListMsg(const lm::helloworld &msg)
{
    cout << msg.id() << endl;
    cout << msg.str() << endl;
}

int main(int argc, char *argv[])
{

    lm::HelloWorld msg1;

    {
        fstream input("./log", ios::in | ios::binary);
        if (!msg1.ParseFromIstream(&input))
        {
            printf("Failed to parse address book\n");
            return -1;
        }
    }

    ListMsg(msg1);
    return 0;
}
