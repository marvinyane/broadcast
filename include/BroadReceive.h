#include <vector>
#include "utils/Thread.h"
#include "BroadMessage.h"

class BroadReceive : public android::Thread
{
    public:
        // start thread to listen?
        BroadReceive();
        virtual ~BroadReceive();

        void start();

        // how filter?
        int filter(const std::vector<int>& f);

        // handle message in receiver thread? take care?
        virtual void handleMessage(android::sp<BroadMessage> message) = 0;

    private:
        BroadReceive(const BroadReceive&);
        BroadReceive& operator=(const BroadReceive&);

        static void* onHandle(void*);
        void onHandleMessage();

        virtual bool threadLoop();

    private:
        struct Private;
        Private *pri;

        android::sp<BroadMessage> message;


};
