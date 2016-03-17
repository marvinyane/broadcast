#ifndef __BROADMESSAGEPRIVATE_H__
#define __BROADMESSAGEPRIVATE_H__

#include <stdio.h>
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


class BroadMessageImpl
{
    public:
        BroadMessageImpl(int id)
        {
            char tmp[STC_MESSAGE_OBJECT_PREFIX_LEN + 5];
            memcpy(tmp, STC_MESSAGE_OBJECT_PREFIX, STC_MESSAGE_OBJECT_PREFIX_LEN);
            sprintf(tmp+STC_MESSAGE_OBJECT_PREFIX_LEN, "%04x", id);
            tmp[sizeof(tmp)-1] = 0;

            msg = dbus_message_new_signal(STC_MESSAGE_PATH_NAME,
                    STC_MESSAGE_INTERFACE_NAME,
                    tmp);

            if (msg) {
                dbus_message_iter_init_append(msg, &iter);
            }
            else {
                // throw?
                LOGE("dbus message new failed.");
            }

            LOGD("dbus message signal created. \n");

        }

        BroadMessageImpl(char* buf, int len)
        {
            DBusError err;
            dbus_error_init(&err);

            msg = dbus_message_demarshal(buf, len, &err);

            if (dbus_error_is_set(&err))
            {
                // TODO:
            }

            if (msg)
            {
                dbus_message_iter_init(msg, &iter);
            }

            dbus_error_free(&err);
        }

        ~BroadMessageImpl()
        {
            if (msg)
            {
                dbus_message_unref(msg);
            }
        }

        std::string getData()
        {
            char* buf = NULL;
            int len = 0;

            // TODO:
            dbus_message_set_serial(msg, 1);

            if (!dbus_message_marshal(msg, &buf, &len)) {
                LOGE("marshaled is failed....\n");
            }

            return std::string(buf, len);
        }


        int current_type()
        {
            return dbus_message_iter_get_arg_type(&iter);
        }

        bool at_end()
        {
            return current_type() == DBUS_TYPE_INVALID;
        }

        bool has_next()
        {
            return dbus_message_iter_has_next(&iter);
        }

        bool append_basic(int type_id, void *value)
        {
            return dbus_message_iter_append_basic(&iter, type_id, value);
        }

        void get_basic(int type_id, void *ptr)
        {
            if (current_type() == type_id) {
                dbus_message_iter_get_basic(&iter, ptr);
                dbus_message_iter_next(&iter);
            }
            else
            {
                LOGD("current type is %d, type id is %d\n", current_type(), type_id);
            }
        }

        bool append_byte(unsigned char byte)
        {
            return append_basic(DBUS_TYPE_BYTE, &byte);
        }

        unsigned char get_byte()
        {
            char c;
            get_basic(DBUS_TYPE_BYTE, &c);

            return c;
        }

        bool append_int16(signed short i)
        {
            return append_basic(DBUS_TYPE_INT16, &i);
        }

        signed short get_int16()
        {
            signed short i = 0;
            get_basic(DBUS_TYPE_INT32, &i);

            return i;
        }

        bool append_int32(signed int i)
        {
            return append_basic(DBUS_TYPE_INT32, &i);
        }

        signed int get_int32()
        {
            int i = 0;
            get_basic(DBUS_TYPE_INT32, &i);

            return i;
        }


        bool append_string(const char *chars)
        {
            return append_basic(DBUS_TYPE_STRING, &chars);
        }

        const char *get_string()
        {
            char *chars;
            get_basic(DBUS_TYPE_STRING, &chars);
            return chars;
        }

        bool append_uint32(unsigned int u)
        {
            return append_basic(DBUS_TYPE_UINT32, &u);
        }

        unsigned int get_uint32()
        {
            unsigned int u;
            get_basic(DBUS_TYPE_UINT32, &u);
            return u;
        }

        bool append_uint16(unsigned short u)
        {
            return append_basic(DBUS_TYPE_UINT16, &u);
        }

        unsigned short get_uint16()
        {
            unsigned short u;
            get_basic(DBUS_TYPE_UINT16, &u);
            return u;
        }


        bool append_bool(bool b)
        {
            dbus_bool_t db = b ? TRUE : FALSE;
            return append_basic(DBUS_TYPE_BOOLEAN, &db);
        }

        bool get_bool()
        {
            dbus_bool_t db;
            get_basic(DBUS_TYPE_BOOLEAN, &db);
            return db ? true : false;
        }

        signed long long get_int64()
        {
            signed long long i;
            get_basic(DBUS_TYPE_INT64, &i);
            return i;
        }

        bool append_int64(signed long long i)
        {
            return append_basic(DBUS_TYPE_INT64, &i);
        }

        unsigned long long get_uint64()
        {
            unsigned long long u;
            get_basic(DBUS_TYPE_UINT64, &u);
            return u;
        }

        bool append_uint64(unsigned long long u)
        {
            return append_basic(DBUS_TYPE_UINT64, &u);
        }

        double get_double()
        {
            double d;
            get_basic(DBUS_TYPE_DOUBLE, &d);
            return d;
        }

        bool append_double(double d)
        {
            return append_basic(DBUS_TYPE_DOUBLE, &d);
        }

        bool append_array(char type, const void *ptr, int length)
        {
            DBusMessageIter sub;
            dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "i", &sub);

            dbus_message_iter_append_fixed_array(&sub, type, ptr, length);

            dbus_message_iter_close_container(&iter, &sub);

            return true;
        }

        int array_type()
        {
            return dbus_message_iter_get_element_type(&iter);
        }

        int get_array(void *ptr)
        {
            int length;

            DBusMessageIter sub;
            dbus_message_iter_recurse(&iter, &sub);

            dbus_message_iter_get_fixed_array(&sub, ptr, &length);

            return length;
        }

        bool is_array()
        {
            return dbus_message_iter_get_arg_type(&iter) == DBUS_TYPE_ARRAY;
        }
    private:
        DBusMessageIter iter;
        DBusMessage     *msg;
};

#endif
