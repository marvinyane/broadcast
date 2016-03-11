#include "utils/RefBase.h"

class BroadMessage;

class BroadSignal
{
    public:
        BroadSignal();
        virtual ~BroadSignal();
        int broadcast(android::sp<BroadMessage> message);

    private:
        BroadSignal(const BroadSignal&);
        BroadSignal& operator=(const BroadSignal&);

    private:
        struct Private;
        Private *pri;

};
