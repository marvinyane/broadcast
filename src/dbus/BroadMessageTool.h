#include "BroadMessage.h"
#include "BroadMessageImpl.h"

class BroadMessageTool
{
public:
    BroadMessageTool(BroadMessage* msg)
        : m_msg(msg)
    {
    }

    bool append_byte(unsigned char byte)
    {
        return m_msg->m_impl->append_byte(byte);
    }

    unsigned char get_byte()
    {
        return m_msg->m_impl->get_byte();
    }

    bool append_bool(bool b)
    {
        return m_msg->m_impl->append_bool(b);
    }

    bool get_bool()
    {
        return m_msg->m_impl->get_bool();
    }

    bool append_int16(signed short i)
    {
        return m_msg->m_impl->append_int16(i);
    }

    signed short get_int16()
    {
        return m_msg->m_impl->get_int16();
    }

    bool append_uint16(unsigned short u)
    {
        return m_msg->m_impl->append_uint16(u);
    }

    unsigned short get_uint16()
    {
        return m_msg->m_impl->get_uint16();
    }

    bool append_int32(signed int i)
    {
        return m_msg->m_impl->append_int32(i);
    }

    signed int get_int32()
    {
        return m_msg->m_impl->get_int32();
    }

    bool append_uint32(unsigned int u)
    {
        return m_msg->m_impl->append_uint32(u);
    }

    unsigned int get_uint32()
    {
        return m_msg->m_impl->get_uint32();
    }

    bool append_int64(signed long long i)
    {
        return m_msg->m_impl->append_int64(i);
    }

    signed long long get_int64()
    {
        return m_msg->m_impl->get_int64();
    }

    bool append_uint64(unsigned long long i)
    {
        return m_msg->m_impl->append_uint64(i);
    }

    unsigned long long get_uint64()
    {
        return m_msg->m_impl->get_uint64();
    }

    bool append_double(double d)
    {
        return m_msg->m_impl->append_double(d);
    }

    double get_double()
    {
        return m_msg->m_impl->get_double();
    }

    bool append_string(const char *chars)
    {
        return m_msg->m_impl->append_string(chars);
    }

    const char *get_string()
    {
        return m_msg->m_impl->get_string();
    }

    bool append_array(char type, const void *ptr, int length)
    {
        return m_msg->m_impl->append_array(type, ptr, length);
    }

    int array_type()
    {
        return m_msg->m_impl->array_type();
    }

    int get_array(void *ptr)
    {
        return m_msg->m_impl->get_array(ptr);
    }

    bool is_array()
    {
        return m_msg->m_impl->is_array();
    }
private:
    BroadMessage* m_msg;
};
