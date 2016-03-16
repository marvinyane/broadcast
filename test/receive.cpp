#include <vector>

#include "BroadMessageList.h"
#include "BroadReceive.h"


class testReceive : public BroadReceive
{
    public:
        testReceive()
        {
            std::vector<int> f;
            f.push_back(STC_BROADMESSAGE_TEST_1);

            filter(f);
        }
        void handleMessage(BroadMessageSp sp)
        {
            int id = sp->getId();

            switch (id)
            {
                case STC_BROADMESSAGE_TEST_1:
                    StcBroadMessageTest1Sp msg = std::static_pointer_cast<StcBroadMessageTest1>(sp);
                    printf("name is %s, age is %d\n", msg->getName().c_str(), msg->getAge());
                    break;
            }
        }
};

int main()
{
    testReceive recv;
    recv.start();

    while (1)
    {
        sleep(100);
    }

    return 0;
}
