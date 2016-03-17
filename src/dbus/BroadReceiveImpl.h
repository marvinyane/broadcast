#ifndef __BROADRECEIVEPRIVATE_H__
#define __BROADRECEIVEPRIVATE_H__

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "dbus/dbus.h"

#include "BroadSignalImpl.h"
#include "BroadMessageFactory.h"

#ifndef LOGD
#define LOGD printf
#define LOGE printf
#endif


class BroadReceiveImpl
{
    public:
        BroadReceiveImpl(BroadReceiveMessageHandler* handler)
            : m_handler (handler)
        {
            // create connection
            DBusError err;
            dbus_error_init(&err);

            conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);

            if (dbus_error_is_set(&err)) {
                LOGE("receive bus get failed.");
            }

            if (conn == NULL) {
                LOGE("receive bus connection is null.");
            }

#if 0
            // replace name ?
            int ret = dbus_bus_request_name(conn,
                    "stc.signal.sink",
                    DBUS_NAME_FLAG_REPLACE_EXISTING,
                    &err);

            // check err and ret
#endif
            dbus_error_free(&err);

        }

        void start()
        {
            pthread_create(&tid, NULL, &BroadReceiveImpl::threadRun, this);
        }

        void stop()
        {
        }

        int filter(const std::vector<int>& f)
        {
            DBusError err;
            dbus_error_init(&err);

            const char * tmp = "type='signal',interface='test.signal.Type',member='Test_%04X'";
            char tmp_new[100];

            for (auto it = f.begin(); it != f.end(); it++)
            {
                sprintf(tmp_new, tmp, *it);
                dbus_bus_add_match(conn,
                        tmp_new,
                        &err);

                if (dbus_error_is_set(&err))
                {
                    LOGD("dbus add match %d failed.\n", *it);
                }
            }

            dbus_connection_flush(conn);

            dbus_error_free(&err);

            return 0;

        }
        bool threadLoop()
        {
            dbus_connection_read_write(conn, 0);
            DBusMessage* msg = dbus_connection_pop_message(conn);

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
                    char* buf = NULL;
                    int len = 0;
                    int id = atoi(mem+5);

                    DBusMessageIter dbus_iter;
                    dbus_message_iter_init(msg, &dbus_iter);

                    DBusMessageIter sub;
                    dbus_message_iter_recurse(&dbus_iter, &sub);

                    dbus_message_iter_get_fixed_array(&sub, &buf, &len);

                    BroadMessageFactory factory;
                    BroadMessageSp message = factory.createBroadMessage(buf, len);
                    m_handler->handleMessage(message);
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


            return true;
        }       

        static void* threadRun(void* args)
        {
            BroadReceiveImpl* recv = (BroadReceiveImpl*)args;
            while (1) 
            {
                recv->threadLoop();
            }

            return NULL;

        }
    private:
        DBusConnection* conn;
        pthread_t tid;
        BroadReceiveMessageHandler* m_handler;
};


#endif
