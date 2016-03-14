#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    testReceiveSp recv(new testReceive);
    recv->start();

    sleep(20);

    return 0;
}
