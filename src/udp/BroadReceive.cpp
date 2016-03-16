#include "BroadMessage.h"
#include "BroadReceive.h"
#include "BroadReceiveImpl.h"

#include <stdio.h>

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
    m_impl->filter(f);
}

void BroadReceive::start()
{
}

void BroadReceive::stop()
{
}
