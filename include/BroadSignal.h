#include "BroadMessage.h"

class BroadSignal
{
    public:
        BroadSignal();
        virtual ~BroadSignal();
        int broadcast(BroadMessageSp message);

    private:
        BroadSignal(const BroadSignal&);
        BroadSignal& operator=(const BroadSignal&);

    private:
        struct Private;
        Private *pri;

};
