#ifndef __BROADSIGNALPRIVATE_H__
#define __BROADSIGNALPRIVATE_H__

#include <stdio.h>
#include "dbus/dbus.h"

#ifndef LOGD
#define LOGD printf
#define LOGE printf
#endif


class BroadSignalImpl
{
public:
    BroadSignalImpl()
    {
        // create connection
        DBusError err;
        dbus_error_init(&err);

        conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);

        if (dbus_error_is_set(&err)) {
            // TODO
            LOGD("dbus get error.");
        }

        if (conn == NULL) {
            // TODO: throw?
            LOGD("dbus connection is null");
        }

#if 0
        // replace name ?
        int ret = dbus_bus_request_name(conn,
                                        "stc.signal.source",
                                        DBUS_NAME_FLAG_REPLACE_EXISTING,
                                        &err);

        LOGD("signal request name is %d.\n", ret);

        // check ret
#endif

        dbus_error_free(&err);

    }

    int broadcast(BroadMessageSp msg)
    {
        const std::string& data = msg->getData();
        DBusError err;
        dbus_error_init(&err);
        DBusMessage* dmsg = dbus_message_demarshal(data.data(), data.length(), &err);

        if (dbus_error_is_set(&err)) {
            LOGD("demarshal is error!!! dmsg is %p\n", dmsg);
        }

        dbus_uint32_t serial;
        dbus_connection_send(conn, dmsg, &serial);
        dbus_connection_flush(conn);

        dbus_error_free(&err);
    }

private:
    DBusConnection* conn;
};

#endif
