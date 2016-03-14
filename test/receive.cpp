#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    testReceiveSp recv;
    recv->start();

    while (1) {
        sleep(100);
    }

    return 0;
}
