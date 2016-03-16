#include <stdio.h>
#include <string.h>

#include "BroadMessage.h"
#include "BroadMessageImpl.h"

#define LOGE printf
#define LOGD printf


BroadMessage::BroadMessage(int id)
    : m_id (id)
    , m_data()
    , m_impl(new BroadMessageImpl(id))
{
}

BroadMessage::BroadMessage(int id, char* buf, int len)
    : m_id (id)
    , m_impl(new BroadMessageImpl(buf, len))
{
}

BroadMessage::~BroadMessage()
{
    delete m_impl;
}

const std::string& BroadMessage::getData()
{
    m_data = m_impl->getData();
    return m_data;
}

void BroadMessage::setData(char* buf, int len)
{
    m_data = std::string(buf, len);
    
    if (m_impl)
    {
        delete m_impl;
    }

    m_impl = new BroadMessageImpl(buf, len);
}
