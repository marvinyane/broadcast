#ifndef __BROADMESSAGEFACTORY_H__
#define __BROADMESSAGEFACTORY_H__


#include <memory>

#include "BroadMessage.h"
#include "BroadMessageList.h"

class BroadMessageFactory
{
    public:
        std::shared_ptr<BroadMessage> createBroadMessage(int id, BroadMessage::Private* pri)
        {
            switch (id)
            {
                case STC_BROADMESSAGE_TEST_1:
                    return std::make_shared<StcBroadMessageTest1>(id, pri);

                case STC_BROADMESSAGE_TEST_2:
                    return std::make_shared<StcBroadMessageTest2>(id, pri);

                //defualt:

            }

            return std::make_shared<BroadGeneralMessage>(id, pri);
        }
};


#endif
