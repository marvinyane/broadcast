#ifndef __BROADMESSAGE_H__
#define __BROADMESSAGE_H__

class BroadSignal;
class BroadReceive;

class BroadMessage
{
    public:
        struct Private;

        // this is for writer
        BroadMessage(int id);

        // this is for reader
        BroadMessage(int id, Private* pri);

        virtual ~BroadMessage();

        int getId() 
        {
             return m_id;
        }

        int current_type();

        bool at_end();

        bool has_next();

        BroadMessage& operator++ ();

        bool append_byte(unsigned char byte);

        unsigned char get_byte();

        bool append_bool(bool b);

        bool get_bool();

        bool append_int16(signed short i);

        signed short get_int16();

        bool append_uint16(unsigned short u);

        unsigned short get_uint16();

        bool append_int32(signed int i);

        signed int get_int32();

        bool append_uint32(unsigned int u);

        unsigned int get_uint32();

        bool append_int64(signed long long i);

        signed long long get_int64();

        bool append_uint64(unsigned long long i);

        unsigned long long get_uint64();

        bool append_double(double d);

        double get_double();

        bool append_string(const char *chars);

        const char *get_string();

        bool append_array(char type, const void *ptr, int length);

        int array_type();

        int get_array(void *ptr);

        bool is_array();

    private:
        Private* pri;

        int m_id;

        bool append_basic(int type_id, void *value);
        void get_basic(int type_id, void *ptr);

        virtual void pack() = 0;
        virtual void unpack() = 0;

 friend class BroadSignal;

};


#endif
