#include "BroadMessage.h"
#include "BroadMessageImpl.h"

BroadMessage::BroadMessage(int id)
    : m_id (id)
    , m_data()
    , m_impl(new BroadMessageImpl)
{
}

BroadMessage::BroadMessage(int id, char* buf, int len)
    : m_id (id)
    , m_data(buf, len)
    , m_impl(new BroadMessageImpl)
{
}

void BroadMessage::setData(char* buf, int len)
{
    m_data = std::string(buf, len);
}

const std::string& BroadMessage::getData()
{
    return m_data;
}

BroadMessage::~BroadMessage()
{
    delete m_impl;
}
