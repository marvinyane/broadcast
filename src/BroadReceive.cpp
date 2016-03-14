#include <stdio.h>
#include <string.h>
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

    dbus_error_free(&err);

}

BroadReceive::~BroadReceive()
{
    dbus_connection_close(pri->conn);
}

int BroadReceive::filter(const std::vector<int>& f)
{
    DBusError err;
    dbus_error_init(&err);

    char * tmp = "type='signal',interface='test.signal.Type',member='Test_%04X'";
    char tmp_new[100];

    for (auto it = f.begin(); it != f.end(); it++)
    {
        sprintf(tmp_new, tmp, *it);
        dbus_bus_add_match(pri->conn,
                tmp_new,
                &err);

        if (dbus_error_is_set(&err))
        {
            LOGD("dbus add match %d failed.\n", *it);
        }
    }

    dbus_connection_flush(pri->conn);
    
    dbus_error_free(&err);

    return 0;
}

void* BroadReceive::threadRun(void* args)
{
    BroadReceive* recv = (BroadReceive*)args;
    while (1) 
    {
        recv->threadLoop();
    }

    return NULL;
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


    const char* inter = dbus_message_get_interface(msg);

    if (strncmp(inter, STC_MESSAGE_INTERFACE_NAME, STC_MESSAGE_INTERFACE_NAME_LEN) == 0) 
    {
        const char* mem = dbus_message_get_member(msg);
        if (strncmp(mem, STC_MESSAGE_OBJECT_PREFIX, STC_MESSAGE_OBJECT_PREFIX_LEN) == 0) 
        {
            int id = atoi(mem+5);

            BroadMessageFactory factory;
            BroadMessage::Private* pri = new BroadMessage::Private(msg);
            message = factory.createBroadMessage(id, pri);
            this->handleMessage(message);
        }
        else
        {
            LOGD("receive signal is %s\n", mem);
        }
    }
    else 
    {
        LOGD("receive interface is  %s \n", inter);
    }


#if 0
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
#endif

    return true;
}
