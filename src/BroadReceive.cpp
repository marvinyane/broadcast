#include <stdio.h>
#include <pthread.h>

#include "BroadReceive.h"
#include "BroadReceivePrivate.h"
#include "BroadMessage.h"
#include "BroadMessagePrivate.h"

#include "BroadMessageFactory.h"

#define LOGD printf
#define LOGE printf


BroadReceive::BroadReceive()
{
    // create connection
    DBusError err;
    dbus_error_init(&err);

    pri = new BroadReceive::Private;

    pri->conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);

    if (dbus_error_is_set(&err)) {
        // TODO
        LOGE("receive bus get failed.");
    }

    if (pri->conn == NULL) {
        // TODO: throw?
        LOGE("receive bus connection is null.");
    }

    // replace name ?
    int ret = dbus_bus_request_name(pri->conn,
                                    "stc.signal.sink",
                                    DBUS_NAME_FLAG_REPLACE_EXISTING,
                                    &err);

    // check err and ret

    // add filter?
    dbus_bus_add_match(pri->conn,
                       "type='signal',interface='test.signal.Type'",
                       &err);


    if (dbus_error_is_set(&err))
    {
        LOGD("dbus add match failed.\n");
    }
    // check err

    dbus_connection_flush(pri->conn);

}

BroadReceive::~BroadReceive()
{
    dbus_connection_close(pri->conn);
}

void* BroadReceive::threadRun(void* args)
{
    BroadReceive* recv = (BroadReceive*)args;
    while (1) 
    {
        recv->threadLoop();
    }
}

void BroadReceive::start()
{
    LOGD("start run broad receive thread");

    pthread_create(&tid, NULL, &BroadReceive::threadRun, this);
}

bool BroadReceive::threadLoop()
{
    dbus_connection_read_write(pri->conn, 0);
    DBusMessage* msg = dbus_connection_pop_message(pri->conn);

    if (msg == NULL) {
        sleep(1);
        return true;
    }

    BroadMessageFactory factory;

    if (dbus_message_is_signal(msg, "test.signal.Type", "Test")) 
    {
        BroadMessage::Private* pri = new BroadMessage::Private(msg);
        message = factory.createBroadMessage(STC_BROADMESSAGE_TEST_1, pri);
        this->handleMessage(message);
    }
    else
    {
        LOGD("this is not signal type\n");
        int ret = dbus_message_get_type(msg);
        LOGD("type is %d\n", ret);
        sleep(1);
        return true;
    }
LOGD("handle message stop?\n");

    return true;
}
