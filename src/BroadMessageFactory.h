#ifndef __BROAD_MESSAGE_FACTORY_H__
#define __BROAD_MESSAGE_FACTORY_H__

#include "utils/RefBase.h"
#include "BroadMessage.h"
#include "BroadMessageList.h"

class BroadMessageFactory
{
    public:
        android::sp<BroadMessage> createBroadMessage(int id, BroadMessage::Private* pri)
        {
            switch (id)
            {
                case STC_BROADMESSAGE_TEST_1:
                    return new StcBroadMessageTest1(id, pri);

                case STC_BROADMESSAGE_TEST_2:
                    return new StcBroadMessageTest2(id, pri);

                //defualt:

            }

            return new BroadGeneralMessage(id, pri);
        }
};

#endif
