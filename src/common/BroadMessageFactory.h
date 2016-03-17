#ifndef __BROADMESSAGEFACTORY_H__
#define __BROADMESSAGEFACTORY_H__


#include <memory>

#include "BroadMessage.h"
#include "BroadMessageList.h"
#include "script/StcBroadMessageHeader_generated.h"

class BroadMessageFactory
{
    public:
        BroadMessageSp createBroadMessage(char* buf, int len)
        {
            const BroadFlat::StcBroadMessageHeader* msg = BroadFlat::GetStcBroadMessageHeader(buf);

            switch (msg->id())
            {
                case STC_BROADMESSAGE_TEST_1:
                    return std::make_shared<StcBroadMessageTest>(msg->id(), buf, len);

            }

            return std::make_shared<BroadGeneralMessage>(msg->id(), buf, len);
        }
};


#endif
