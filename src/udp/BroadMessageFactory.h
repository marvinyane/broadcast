#ifndef __BROADMESSAGEFACTORY_H__
#define __BROADMESSAGEFACTORY_H__

#include <memory>

#include "test_generated.h"
#include "BroadMessage.h"
#include "BroadMessageList.h"

class BroadMessageFactory
{
    public:
        BroadMessageSp createMessage(char* buf, int len)
        {
            const TestFlat::StcTestMessage* obj = TestFlat::GetStcTestMessage((uint8_t*)buf);
            int id = obj->id();

            switch (id)
            {
                case STC_BROADMESSAGE_TEST_1:
                    BroadMessageSp sp = std::make_shared<StcBroadMessageTest1>(id, buf, len);
                    return sp;
            }


        }
};

#endif
