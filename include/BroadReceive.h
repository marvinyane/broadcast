#include <memory>
#include "BroadMessage.h"

class BroadReceive
{
    public:
        // start thread to listen?
        BroadReceive();
        virtual ~BroadReceive();

        void start();

        // how filter?
        int filter();

        // handle message in receiver thread? take care?
        virtual void handleMessage(std::shared_ptr<BroadMessage> message) = 0;
        
        bool threadLoop();

        static void* threadRun(void* args);

    private:
        BroadReceive(const BroadReceive&);
        BroadReceive& operator=(const BroadReceive&);

        static void* onHandle(void*);
        void onHandleMessage();


    private:
        struct Private;
        Private *pri;


        pthread_t tid;

        std::shared_ptr<BroadMessage> message;


};
