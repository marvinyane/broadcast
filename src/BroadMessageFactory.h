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
                    return std::make_shared<StcBroadMessageTest1>(STC_BROADMESSAGE_TEST_1, pri);

                defualt:
                    return std::make_shared<StcBroadMessageTest1>(0, pri);

            }
        }
};

