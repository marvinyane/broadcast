#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    BroadMessageSp msg(new StcBroadMessageTest1("marvin", 26));
    BroadSignal signal;
    signal.broadcast(msg);


    int _array[] = {3, 45, 67, 98, 100, 1, 2, 3, 4, 5};
    BroadMessageSp msg1(new StcBroadMessageTest2("tom", 27, (int*)_array, 10));
    signal.broadcast(msg1);
    
    
    BroadMessageSp msg3(new BroadGeneralMessage(STC_BROADMESSAGE_TEST_3));
    signal.broadcast(msg3);

    while (1) {
        sleep(100);
    }

    return 0;
}
