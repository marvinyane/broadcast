#ifndef __BROADMESSAGEPRIVATE_H__
#define __BROADMESSAGEPRIVATE_H__

#include "dbus/dbus.h"

#define STC_MESSAGE_PATH_NAME "/test/signal/object"

#define STC_MESSAGE_INTERFACE_NAME "test.signal.Type"
#define STC_MESSAGE_INTERFACE_NAME_LEN  (16)

#define STC_MESSAGE_OBJECT_PREFIX   "Test_"
#define STC_MESSAGE_OBJECT_PREFIX_LEN   (5)

struct BroadMessage::Private
{
    DBusMessageIter iter;
    DBusMessage     *msg;

    Private()
        : msg(NULL)
    {
    }

    Private(DBusMessage* _msg)
        : msg(_msg)
    {
    }

};

#endif
