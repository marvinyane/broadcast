#ifndef __BROADMESSAGELIST_H__
#define __BROADMESSAGELIST_H__

#include "BroadMessage.h"

#define STC_BROADMESSAGE_TEST_1         (0x0001)
#define STC_BROADMESSAGE_TEST_2         (0x0002)

#define STC_BROADMESSAGE_TEST_3         (0x0003)

// after value define
#include "StcBroadMessageTest1.h"

class BroadGeneralMessage : public BroadMessage
{
    public:
        BroadGeneralMessage(int id)
            : BroadMessage(id)
        {
        }

        BroadGeneralMessage(int id, char* buf, int len)
            : BroadMessage(id, buf, len)
        {
        }

    private:
        void pack()
        {
        }

        void unpack()
        {
        }
};

typedef std::shared_ptr<BroadGeneralMessage> BroadGeneralMessageSp;


#endif
