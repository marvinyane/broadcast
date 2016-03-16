#include "BroadSignal.h"
#include "BroadMessageList.h"

int main()
{
    BroadSignal signal;

    BroadMessageSp msg(new StcBroadMessageTest1("marvin", 26));
    signal.broadcast(msg);

    sleep(10);

    return 0;
}
