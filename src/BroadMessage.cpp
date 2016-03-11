#include <stdio.h>
#include <string.h>

#include "BroadMessage.h"
#include "BroadMessagePrivate.h"

#define LOGE printf
#define LOGD printf


BroadMessage::BroadMessage(int id)
    : m_id (id)
{
    char tmp[STC_MESSAGE_OBJECT_PREFIX_LEN + 5];
    memcpy(tmp, STC_MESSAGE_OBJECT_PREFIX, STC_MESSAGE_OBJECT_PREFIX_LEN);
    sprintf(tmp+STC_MESSAGE_OBJECT_PREFIX_LEN, "%04x", id);
    tmp[sizeof(tmp)] = 0;

    pri = new Private;
    pri->msg = dbus_message_new_signal(STC_MESSAGE_PATH_NAME,
                                       STC_MESSAGE_INTERFACE_NAME,
                                       tmp);

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


bool BroadMessage::append_bool(bool b)
{
	dbus_bool_t db = b ? TRUE : FALSE;
	return append_basic(DBUS_TYPE_BOOLEAN, &db);
}

bool BroadMessage::get_bool()
{
 	dbus_bool_t db;
	get_basic(DBUS_TYPE_BOOLEAN, &db);
	return db ? true : false;
}

signed long long BroadMessage::get_int64()
{
	signed long long i;
	get_basic(DBUS_TYPE_INT64, &i);
	return i;
}

bool BroadMessage::append_int64(signed long long i)
{
	return append_basic(DBUS_TYPE_INT64, &i);
}

unsigned long long BroadMessage::get_uint64()
{
	unsigned long long u;
	get_basic(DBUS_TYPE_UINT64, &u);
	return u;
}

bool BroadMessage::append_uint64(unsigned long long u)
{
	return append_basic(DBUS_TYPE_UINT64, &u);
}

double BroadMessage::get_double()
{
	double d;
	get_basic(DBUS_TYPE_DOUBLE, &d);
	return d;
}

bool BroadMessage::append_double(double d)
{
	return append_basic(DBUS_TYPE_DOUBLE, &d);
}

bool BroadMessage::append_array(char type, const void *ptr, int length)
{
    DBusMessageIter sub;
    dbus_message_iter_open_container(&pri->iter, DBUS_TYPE_ARRAY, "i", &sub);

	dbus_message_iter_append_fixed_array(&sub, type, ptr, length);

    dbus_message_iter_close_container(&pri->iter, &sub);
}

int BroadMessage::array_type()
{
	return dbus_message_iter_get_element_type(&pri->iter);
}

int BroadMessage::get_array(void *ptr)
{
	int length;

    DBusMessageIter sub;
    dbus_message_iter_recurse(&pri->iter, &sub);

	dbus_message_iter_get_fixed_array(&sub, ptr, &length);

	return length;
}

bool BroadMessage::is_array()
{
	return dbus_message_iter_get_arg_type(&pri->iter) == DBUS_TYPE_ARRAY;
}
