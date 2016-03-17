#include <stdio.h>

#include "BroadSignal.h"
#include "BroadSignalImpl.h"

#define LOGD printf
#define LOGE printf

BroadSignal::BroadSignal()
    : m_impl (new BroadSignalImpl)
{
}

BroadSignal::~BroadSignal()
{
    delete m_impl;
}

int BroadSignal::broadcast(BroadMessageSp msg)
{
    m_impl->broadcast(msg->getId(), msg->getData());
    return 0;
}
