#include "BroadMessage.h"


class BroadSignalImpl;

class BroadSignal
{
    public:
        BroadSignal();
        virtual ~BroadSignal();
        int broadcast(BroadMessageSp message);

    private:
        BroadSignalImpl* m_impl;
};
