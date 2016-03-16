#include <stdio.h>

#include "BroadReceive.h"
#include "BroadReceiveImpl.h"

#ifndef LOGD
#define LOGD printf
#define LOGE printf
#endif


BroadReceive::BroadReceive()
    : m_impl (new BroadReceiveImpl(this))
{
}

BroadReceive::~BroadReceive()
{
    delete m_impl;
}

int BroadReceive::filter(const std::vector<int>& f)
{
    return m_impl->filter(f);
}


void BroadReceive::start()
{
    LOGD("start run broad receive thread");
    m_impl->start();
}

