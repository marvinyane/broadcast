#include "BroadMessage.h"
#include "BroadSignal.h"
#include "testReceive.h"

int main()
{
    std::string name = "marvin";
    std::shared_ptr<BroadMessage> msg(new StcBroadMessageTest1(name, 26));
    BroadSignal signal(msg);
    signal.broadcast();

    while (1) {
        sleep(100);
    }

    return 0;
}
