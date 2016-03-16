#ifndef __STCBROADMESSAGETEST1_H__
#define __STCBROADMESSAGETEST1_H__


#include <string.h>
#include <string>

#include "BroadMessage.h"
#include "BroadMessageList.h"
#include "BroadMessageTool.h"

class StcBroadMessageTest1 : public BroadMessage
{
    public:
        // this is for writer
        StcBroadMessageTest1(std::string name, int age)
              : BroadMessage(STC_BROADMESSAGE_TEST_1) 
              , m_name(name)
              , m_age(age)
              , m_tool(this)
        {
            pack();
        }

        // this is for reader!
        StcBroadMessageTest1(int id, char* buf, int len)
            : BroadMessage(id, buf, len)
            , m_name()
            , m_age(0)
            , m_tool(this)
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
            m_tool.append_uint16(m_id);
            m_tool.append_string(m_name.c_str());
            m_tool.append_uint32(m_age);
        }

        void unpack()
        {
            m_id = m_tool.get_uint16();
            m_name = std::string(m_tool.get_string());
            m_age = m_tool.get_uint32();
        }

    private:
        std::string     m_name;
        int             m_age;
        BroadMessageTool m_tool;

};

typedef std::shared_ptr<StcBroadMessageTest1> StcBroadMessageTest1Sp;

#endif
