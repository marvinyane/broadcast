#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main(int argc, char** argv)
{
    testReceiveSp recv(new testReceive(argv[1]));
    recv->start();

    sleep(20);

    return 0;
}
