#ifndef __BROADSIGNALPRIVATE_H__
#define __BROADSIGNALPRIVATE_H__

#include "dbus/dbus.h"

struct BroadSignal::Private
{
    DBusConnection* conn;
};

#endif
