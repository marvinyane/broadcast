#ifndef __BROADRECEIVEPRIVATE_H__
#define __BROADRECEIVEPRIVATE_H__

#include "dbus/dbus.h"

struct BroadReceive::Private
{
    DBusConnection* conn;
};

#endif
