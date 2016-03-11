#ifndef __STC_BROADMESSAGE_TEST_1_H__
#define __STC_BROADMESSAGE_TEST_1_H__

#include <string.h>
#include <string>

#include "BroadMessage.h"

class StcBroadMessageTest1 : public BroadMessage
{
    public:
        // this is for writer
        StcBroadMessageTest1(std::string name, int age)
              : BroadMessage(STC_BROADMESSAGE_TEST_1) 
              , m_name(name)
              , m_age(age)
        {
            pack();
        }

        // this is for reader!
        StcBroadMessageTest1(int id, BroadMessage::Private* pri) 
            : BroadMessage(id, pri)
            , m_name()
            , m_age(0)
        {
            unpack();
        }

        ~StcBroadMessageTest1()
        {
        }

        // to get?
        const std::string& getName()
        {
            return m_name;
        }

        int getAge()
        {
            return m_age;
        }

        // why not set?
        
    private:
        void pack()
        {
            this->append_uint16(m_id);
            this->append_string(m_name.c_str());
            this->append_uint32(m_age);
        }

        void unpack()
        {
            m_id = this->get_uint16();
            m_name = std::string(this->get_string());
            m_age = this->get_uint32();
        }

    private:
        std::string     m_name;
        int             m_age;

};

#endif

