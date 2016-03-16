#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    BroadSignal signal;

    BroadMessageSp msg(new StcBroadMessageTest1("marvin", 26));
    signal.broadcast(msg);

    sleep(10);

    return 0;
}
