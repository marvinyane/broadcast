#ifndef __BROADRECEIVE_H__
#define __BROADRECEIVE_H__

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

        void stop();
        
    private:
        BroadReceiveImpl* m_impl;
};

#endif
