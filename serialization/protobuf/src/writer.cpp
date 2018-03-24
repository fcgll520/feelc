#include "lm.HelloWorld.pb.h"
#include <iostream>
#include <fstream>

using namespace std;
int main(void)
{
    lm::HelloWorld msg1;
    msg1.set_id(101);
    //msg1.set_str("hello");

    // Write the new address book back to disk.
    //fstream output("./log", ios::out | ios::trunc | ios::binary);

    //if (!msg1.SerializeToOstream(&output))
    //{
    //    printf("Failed to write msg\n");
    //    return -1;
    //}
    return 0;
}
