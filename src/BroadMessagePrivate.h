#ifndef __BROADMESSAGEPRIVATE_H__
#define __BROADMESSAGEPRIVATE_H__

#include "dbus/dbus.h"

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
