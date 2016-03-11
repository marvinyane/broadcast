#ifndef __BROADMESSAGELIST_H__
#define __BROADMESSAGELIST_H__

#include "BroadMessage.h"

#define STC_BROADMESSAGE_TEST_1         (0x0001)
#define STC_BROADMESSAGE_TEST_2         (0x0002)

#define STC_BROADMESSAGE_TEST_3         (0x0003)

// after value define
#include "StcBroadMessageTest1.h"
#include "StcBroadMessageTest2.h"

class BroadGeneralMessage : public BroadMessage
{
    public:
        BroadGeneralMessage(int id)
            : BroadMessage(id)
        {
        }

        BroadGeneralMessage(int id, BroadMessage::Private* pri)
            : BroadMessage(id, pri)
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


#endif
