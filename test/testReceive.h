#include <stdio.h>
#include <string>

#include "BroadMessage.h"
#include "BroadReceive.h"

#include "BroadMessageList.h"

#define LOGD printf

class testReceive : public BroadReceive
{
public:
    testReceive()
        : BroadReceive()
    {
        LOGD("start test receive...");
    }

    ~testReceive(){}

    virtual void handleMessage(std::shared_ptr<BroadMessage> message)
    {
        int id = message->getId();
        switch (id)
        {
            case STC_BROADMESSAGE_TEST_1:
            {
                std::shared_ptr<StcBroadMessageTest1> msg = std::static_pointer_cast<StcBroadMessageTest1>(message);
                const std::string& name = msg->getName();
                LOGD("receive message name is %s, age is %d\n", name.c_str(), msg->getAge());
                break;
            }
                
        }
    }
};
