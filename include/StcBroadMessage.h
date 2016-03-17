#ifndef __STCBROADMESSAGETEST1_H__
#define __STCBROADMESSAGETEST1_H__

#include <string.h>
#include <string>

#include "BroadMessage.h"
#include "BroadMessageList.h"
#include "script/StcBroadMessageTest_generated.h"

class StcBroadMessageTest : public BroadMessage
{
    public:
        // this is for writer
        StcBroadMessageTest(std::string name, int age)
              : BroadMessage(STC_BROADMESSAGE_TEST_1) 
              , m_name(name)
              , m_age(age)
        {
            pack();
        }

        // this is for reader!
        StcBroadMessageTest(int id, char* buf, int len)
            : BroadMessage(id, buf, len)
            , m_name()
            , m_age(0)
        {
            unpack();
        }

        ~StcBroadMessageTest()
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

    private:
        void pack()
        {
            flatbuffers::FlatBufferBuilder builder;
            auto name = builder.CreateString(m_name);
            auto flat = BroadFlat::CreateStcBroadMessageTest(builder, m_id, name, m_age);
            builder.Finish(flat);


            char* buf = (char*) builder.GetBufferPointer();
            int len = builder.GetSize();

            setData(buf, len);
        }

        void unpack()
        {
            const std::string& data = getData();

            const BroadFlat::StcBroadMessageTest* obj = BroadFlat::GetStcBroadMessageTest((uint8_t*)data.data());

            m_id = obj->id();
            m_name = obj->name()->data();
            m_age = obj->age();
        }

    private:
        std::string     m_name;
        int             m_age;

};

typedef std::shared_ptr<StcBroadMessageTest> StcBroadMessageTestSp;

#endif
