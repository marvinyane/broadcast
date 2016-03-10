#include <stdio.h>

#include "BroadMessage.h"
#include "BroadMessagePrivate.h"

#define LOGE printf
#define LOGD printf


BroadMessage::BroadMessage(int id)
    : m_id (id)
{
    pri = new Private;
    pri->msg = dbus_message_new_signal("/test/signal/object",
                                       "test.signal.Type",
                                       "Test");

    if (pri->msg) {
        dbus_message_iter_init_append(pri->msg, &pri->iter);
    }
    else {
        // throw?
        LOGE("dbus message new failed.");
    }

}

BroadMessage::BroadMessage(int id, BroadMessage::Private *_pri)
    : m_id (id)
    , pri(_pri)
{
    if (pri->msg) {
        dbus_message_iter_init(pri->msg, &pri->iter);
    }
    else {
        // throw?
    }

}

BroadMessage::~BroadMessage()
{
    // TODO
    dbus_message_unref(pri->msg);
}

int BroadMessage::current_type()
{
    return dbus_message_iter_get_arg_type(&pri->iter);
}

bool BroadMessage::at_end()
{
    return current_type() == DBUS_TYPE_INVALID;
}

bool BroadMessage::has_next()
{
    return dbus_message_iter_has_next(&pri->iter);
}

bool BroadMessage::append_basic(int type_id, void *value)
{
    return dbus_message_iter_append_basic(&pri->iter, type_id, value);
}

void BroadMessage::get_basic(int type_id, void *ptr)
{
    if (current_type() == type_id) {
        dbus_message_iter_get_basic(&pri->iter, ptr);
        dbus_message_iter_next(&pri->iter);
    }
    else
    {
        LOGD("current type is %d, type id is %d\n", current_type(), type_id);
    }
}

bool BroadMessage::append_byte(unsigned char byte)
{
    return append_basic(DBUS_TYPE_BYTE, &byte);
}

unsigned char BroadMessage::get_byte()
{
    char c;
    get_basic(DBUS_TYPE_BYTE, &c);

    return c;
}

bool BroadMessage::append_int32(signed int i)
{
    return append_basic(DBUS_TYPE_INT32, &i);
}

signed int BroadMessage::get_int32()
{
    int i = 0;
    get_basic(DBUS_TYPE_INT32, &i);

    return i;
}


bool BroadMessage::append_string(const char *chars)
{
	return append_basic(DBUS_TYPE_STRING, &chars);
}

const char *BroadMessage::get_string()
{
	char *chars;
	get_basic(DBUS_TYPE_STRING, &chars);
 	return chars;
}

bool BroadMessage::append_uint32(unsigned int u)
{
	return append_basic(DBUS_TYPE_UINT32, &u);
}

unsigned int BroadMessage::get_uint32()
{
	unsigned int u;
	get_basic(DBUS_TYPE_UINT32, &u);
 	return u;
}

bool BroadMessage::append_uint16(unsigned short u)
{
	return append_basic(DBUS_TYPE_UINT16, &u);
}

unsigned short BroadMessage::get_uint16()
{
	unsigned short u;
	get_basic(DBUS_TYPE_UINT16, &u);
 	return u;
}
