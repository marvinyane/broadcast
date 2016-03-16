#ifndef __BROADMESSAGEFACTORY_H__
#define __BROADMESSAGEFACTORY_H__


#include <memory>

#include "BroadMessage.h"
#include "BroadMessageList.h"

class BroadMessageFactory
{
    public:
        BroadMessageSp createBroadMessage(int id, char* buf, int len)
        {
            switch (id)
            {
                case STC_BROADMESSAGE_TEST_1:
                    return std::make_shared<StcBroadMessageTest1>(id, buf, len);

            }

            return std::make_shared<BroadGeneralMessage>(id, buf, len);
        }
};


#endif
