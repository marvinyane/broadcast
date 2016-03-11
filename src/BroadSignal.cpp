#include <stdio.h>

#include "BroadMessage.h"
#include "BroadSignal.h"
#include "BroadSignalPrivate.h"
#include "BroadMessagePrivate.h"

#define LOGD printf
#define LOGE printf

BroadSignal::BroadSignal()
{
    // create connection
    DBusError err;
    dbus_error_init(&err);
    
    pri = new BroadSignal::Private();

    pri->conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);

    if (dbus_error_is_set(&err)) {
        // TODO
        LOGD("dbus get error.");
    }

    if (pri->conn == NULL) {
        // TODO: throw?
        LOGD("dbus connection is null");
    }

    // replace name ?
    int ret = dbus_bus_request_name(pri->conn,
                                    "stc.signal.source",
                                    DBUS_NAME_FLAG_REPLACE_EXISTING,
                                    &err);

    LOGD("signal request name is %d.\n", ret);

    // check ret
}

BroadSignal::~BroadSignal()
{
    dbus_connection_close(pri->conn);
}

int BroadSignal::broadcast(BroadMessageSp message)
{
    dbus_uint32_t serial;
    dbus_connection_send(pri->conn, message->pri->msg, &serial);
    dbus_connection_flush(pri->conn);

    LOGD("signal has sent.\n");

    return 0;
}
