#include "BroadReceive.h"
#include "BroadReceivePrivate.h"
#include "BroadMessage.h"
#include "BroadMessagePrivate.h"

#include "BroadMessageFactory.h"
#define LOG_TAG "libbroadcast"
#include "cutils/log.h"

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

void BroadReceive::start()
{
    LOGD("start run broad receive thread");
    run("BroadReceive");
}

bool BroadReceive::threadLoop()
{
    LOGD("broad receive thread loop.... ");

    while (1) {

        dbus_connection_read_write(pri->conn, 0);
        DBusMessage* msg = dbus_connection_pop_message(pri->conn);

        if (msg == NULL) {
            // return true;
            sleep(1);
            continue;
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
