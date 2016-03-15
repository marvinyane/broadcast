#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

#include "BroadMessage.h"
#include "BroadReceive.h"

#include "BroadMessageList.h"

#define LOGD printf

class testReceive : public BroadReceive
{
public:
    testReceive(char* l)
        : BroadReceive()
    {
        LOGD("start test receive...");
        std::vector<int> f;

        int t = atoi(l);
        if (t == 0)
        {
            f.push_back(STC_BROADMESSAGE_TEST_1);
            f.push_back(STC_BROADMESSAGE_TEST_2);
        }
        else if (t == 1)
        {
            f.push_back(STC_BROADMESSAGE_TEST_1);
            f.push_back(STC_BROADMESSAGE_TEST_3);

        }
        else
        {
            f.push_back(STC_BROADMESSAGE_TEST_1);
            f.push_back(STC_BROADMESSAGE_TEST_2);
            f.push_back(STC_BROADMESSAGE_TEST_3);
        }
        filter(f);
    }

    ~testReceive(){}

    virtual void handleMessage(BroadMessageSp message)
    {
        int id = message->getId();
        switch (id)
        {
            case STC_BROADMESSAGE_TEST_1:
            {
                StcBroadMessageTest1Sp msg = std::static_pointer_cast<StcBroadMessageTest1>(message);
                const std::string& name = msg->getName();
                LOGD("receive message 1 name is %s, age is %d\n", name.c_str(), msg->getAge());
                break;
            }

            case STC_BROADMESSAGE_TEST_2:
            {
                StcBroadMessageTest2Sp msg = std::static_pointer_cast<StcBroadMessageTest2>(message);
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

typedef std::shared_ptr<testReceive> testReceiveSp;
