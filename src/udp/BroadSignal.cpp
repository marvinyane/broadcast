#include "BroadMessage.h"
#include "BroadSignal.h"
#include "BroadSignalImpl.h"

BroadSignal::BroadSignal()
    : m_impl (new BroadSignalImpl)
{
    // create udp send
}

BroadSignal::~BroadSignal()
{
    delete m_impl;
}

int BroadSignal::broadcast(BroadMessageSp msg)
{
    m_impl->broadcast(msg->getData());

    return 0;
}
