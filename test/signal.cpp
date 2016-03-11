#include "BroadMessage.h"
#include "BroadMessageList.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    android::sp<BroadMessage> msg(new StcBroadMessageTest1("marvin", 26));
	BroadSignal signal;
	signal.broadcast(msg);

    int arr[] = {1,2,3,4,5,6,7,8,9,0};
    android::sp<BroadMessage> msg1(new StcBroadMessageTest2("Tom", 27, arr, 10));
    signal.broadcast(msg1);

    android::sp<BroadMessage> msg2(new BroadGeneralMessage(STC_BROADMESSAGE_TEST_3));
    signal.broadcast(msg2);

    while (1) {
        sleep(100);
    }

    return 0;
}
