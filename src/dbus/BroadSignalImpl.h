#ifndef __BROADSIGNALPRIVATE_H__
#define __BROADSIGNALPRIVATE_H__

#include <stdio.h>
#include <string.h>
#include "dbus/dbus.h"

#define STC_MESSAGE_PATH_NAME "/test/signal/object"

#define STC_MESSAGE_INTERFACE_NAME "test.signal.Type"
#define STC_MESSAGE_INTERFACE_NAME_LEN  (16)

#define STC_MESSAGE_OBJECT_PREFIX   "Test_"
#define STC_MESSAGE_OBJECT_PREFIX_LEN   (5)

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

    int broadcast(int id, const std::string& data)
    {
        DBusMessage *dbus_msg;
        DBusMessageIter dbus_iter;

        char tmp[STC_MESSAGE_OBJECT_PREFIX_LEN + 5];
        memcpy(tmp, STC_MESSAGE_OBJECT_PREFIX, STC_MESSAGE_OBJECT_PREFIX_LEN);
        sprintf(tmp+STC_MESSAGE_OBJECT_PREFIX_LEN, "%04x", id);
        tmp[sizeof(tmp)-1] = 0;

        dbus_msg = dbus_message_new_signal(STC_MESSAGE_PATH_NAME,
                STC_MESSAGE_INTERFACE_NAME,
                tmp);

        if (dbus_msg) {
            dbus_message_iter_init_append(dbus_msg, &dbus_iter);
        }
        else {
            // throw?
            LOGE("dbus message new failed.");
        }

        DBusMessageIter sub;
        dbus_message_iter_open_container(&dbus_iter, DBUS_TYPE_ARRAY, "y", &sub);

        const char* buf = data.data();

        dbus_message_iter_append_fixed_array(&sub, DBUS_TYPE_BYTE, &buf, data.length());

        dbus_message_iter_close_container(&dbus_iter, &sub);

        dbus_uint32_t serial;
        dbus_connection_send(conn, dbus_msg, &serial);
        dbus_connection_flush(conn);


        dbus_message_unref(dbus_msg);

        return 0;
    }

private:
    DBusConnection* conn;
};

#endif
