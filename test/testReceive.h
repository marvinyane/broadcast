#include "BroadMessage.h"
#include "BroadReceive.h"
#include "BroadMessageList.h"
#define LOG_TAG "libbroadcast"

#include "cutils/log.h"
#include "utils/RefBase.h"

class testReceive : public BroadReceive
{
public:
    testReceive()
        : BroadReceive()
    {
        LOGD("start test receive...");
    }

    ~testReceive(){}

    virtual void handleMessage(android::sp<BroadMessage> message)
    {
        int id = message->getId();
        switch (id)
        {
            case STC_BROADMESSAGE_TEST_1:
            {
                android::sp<StcBroadMessageTest1> msg = static_cast<StcBroadMessageTest1*>(message.get());
                const std::string& name = msg->getName();
                LOGD("receive message 1 name is %s, age is %d\n", name.c_str(), msg->getAge());
                break;
            }

            case STC_BROADMESSAGE_TEST_2:
            {
                android::sp<StcBroadMessageTest2> msg = static_cast<StcBroadMessageTest2*>(message.get());
                const std::string& name = msg->getName();
                LOGD("receive message 2 name is %s, age is %d\n", name.c_str(), msg->getAge());
                int* _array = msg->getArray();
                for (int i = 0; i < 5; i++)
                {
                    LOGD("array[%d] is %d\n", i, _array[i]);
                }
                break;
            }
            case STC_BROADMESSAGE_TEST_3:
            {
                LOGD("receive test message 3.... \n");
                break;
            }


                
        }
    }
};

typedef android::sp<testReceive> testReceiveSp;
