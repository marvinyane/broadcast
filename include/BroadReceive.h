#include <memory>
#include <vector>

#include "BroadMessage.h"

class BroadReceiveImpl;

class BroadReceiveMessageHandler
{
public:
    virtual void handleMessage(BroadMessageSp msg) = 0;
};

class BroadReceive : public BroadReceiveMessageHandler
{
    public:
        // start thread to listen?
        BroadReceive();
        virtual ~BroadReceive();

        void start();

        // how filter?
        int filter(const std::vector<int>& f);

        // handle message in receiver thread? take care?
        virtual void handleMessage(BroadMessageSp message) = 0;
        

    private:
        BroadReceive(const BroadReceive&);
        BroadReceive& operator=(const BroadReceive&);

    private:
        BroadReceiveImpl* m_impl;
};
